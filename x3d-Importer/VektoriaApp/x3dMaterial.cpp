#include "x3dMaterial.h"
#include "x3dObject.h"


x3dMaterial::x3dMaterial(std::string infos, std::vector<Pair<std::string, x3dMaterial*>> &materialDef )
{
	this->info = infos;
	this->info = this->info.substr(this->info.find("<material") + 9);
	this->info = this->info.substr(0, this->info.find("/>", 0));

	if (this->info.find("def=") != std::string::npos) {

		setParams();

		std::string temp = this->info.substr(this->info.find("def=") + 5);
		temp = temp.substr(0, temp.find("\"", 0));
		materialDef.emplace_back();
		materialDef.back().setA(temp);
		materialDef.back().setB(this);
	}
	else if (this->info.find("use=") != std::string::npos) {
		std::string temp = this->info.substr(this->info.find("use=") + 5);
		temp = temp.substr(0, temp.find("\"", 0));
		for (auto material : materialDef) {
			if (temp == material.getA()) {
				*this = *material.getB();
			}
		}
	}
	else {
		setParams();
	}


}

x3dMaterial::~x3dMaterial()
{
}

void x3dMaterial::setDiffuceColor()
{
	
	if (this->info.find("diffusecolor") != std::string::npos) {
		this->diffusecolor = x3dObject::extractVector3D("diffusecolor", this->info);
	}
}

void x3dMaterial::setEmissiveColor()
{
	if (this->info.find("emissivecolor") != std::string::npos) {
		this->emissiveColor = x3dObject::extractVector3D("emissivecolor", this->info);
	}
}

void x3dMaterial::setSpecularColor()
{
	if (this->info.find("specularcolor") != std::string::npos) {
		this->specularColor = x3dObject::extractVector3D("specularcolor", this->info);
	}
}

void x3dMaterial::setAmbientIntensity()
{
	if (this->info.find("ambientintensity") != std::string::npos) {
		this->ambientIntensity = x3dObject::extractFloat("ambientintensity", this->info);
	}
}

void x3dMaterial::setShininess()
{
	if (this->info.find("shininess") != std::string::npos) {
		this->shininess = x3dObject::extractFloat("shininess", this->info);
	}
}

void x3dMaterial::setTransparency()
{
	if (this->info.find("transparency") != std::string::npos) {
		this->transparency = x3dObject::extractFloat("transparency", this->info);
	}
}

void x3dMaterial::setParams()
{
	setDiffuceColor();
	setEmissiveColor();
	setSpecularColor();
	setAmbientIntensity();
	setShininess();
	setTransparency();
}

Vector3D x3dMaterial::getDiffuseColor()
{
	return this->diffusecolor;
}

Vector3D x3dMaterial::getEmissiveColor()
{
	return this->emissiveColor;
}

Vector3D x3dMaterial::getSpecularColor()
{
	return this->specularColor;
}

float x3dMaterial::getAmbientIntensity()
{
	return this->ambientIntensity;
}

float x3dMaterial::getShininess()
{
	return this->shininess;
}

float x3dMaterial::getTransparency()
{
	return this->transparency;
}
