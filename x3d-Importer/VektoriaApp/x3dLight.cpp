#include "x3dLight.h"

x3dLight::x3dLight(int start, std::string info, int id)
{
}

x3dLight::x3dLight()
{
}

x3dLight::~x3dLight()
{
}

Vector3D x3dLight::getColor()
{
	return this->lightColor;
}

float x3dLight::getIntensity()
{
	return this->intensity;
}

float x3dLight::getAmbientIntensity()
{
	return this->ambientIntensity;
}

bool x3dLight::getOn()
{
	return this->on;
}

int x3dLight::getShadowMapSize()
{
	return this->shadowMapSize;
}

bool x3dLight::getGlobal()
{
	return this->global;
}

int x3dLight::getShadowFilterSize()
{
	return this->shadowFilterSize;
}

float x3dLight::getShadowIntensity()
{
	return this->shadowIntensity;
}

float x3dLight::getShadowOffset()
{
	return this->shadowOffset;
}

float x3dLight::getZFar()
{
	return this->zFar;
}

float x3dLight::getZNear()
{
	return this->zNear;
}

void x3dLight::createGeneralParameters(std::string info)
{
	if (info.find("ambientintensity") != std::string::npos) {
		this->ambientIntensity = extractFloat("ambientintensity", info);
	}

	if (info.find("color") != std::string::npos) {
		this->lightColor = extractVector3D("color", info);
	}

	if (info.find(" intensity") != std::string::npos) {
		std::string tmp = info.substr(info.find(" intensity"));
		this->intensity = extractFloat("intensity", tmp);
	}
	if (info.find("\tintensity") != std::string::npos) {
		std::string tmp = info.substr(info.find("\tintensity"));
		this->intensity = extractFloat("\tintensity", tmp);
	}

	if (info.find("on=\"false\"") != std::string::npos)
		this->on = false;

	if (info.find("global=\"true\"") != std::string::npos) {
		this->global = true;
	}
	
	if (info.find("shadowfiltersize") != std::string::npos) {
		this->shadowFilterSize = extractInt("shadowfiltersize", info);
	}
	if (info.find("shadowoffset") != std::string::npos) {
		this->shadowOffset = extractInt("shadowoffset", info);
	}
	if (info.find("shadowintensity") != std::string::npos) {
		this->shadowIntensity = extractInt("shadowintensity", info);
	}
	if (info.find("shadowmapsize") != std::string::npos) {
		this->shadowMapSize = extractInt("shadowmapsize", info);
	}
	if (info.find("znear") != std::string::npos) {
		this->zNear = extractInt("znear", info);
	}
	if (info.find("zfar") != std::string::npos) {
		this->zFar = extractInt("zfar", info);
	}
}

void x3dLight::parseShadowParameters()
{
	
}
