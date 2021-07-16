#include "x3dPointLight.h"

x3dPointLight::x3dPointLight(int start, std::string info, int id)
{
	this->specifier = id;
	this->startingLine = start;
	createGeneralParameters(info);

	if (info.find("radius") != std::string::npos) {
		this->radius = extractFloat("radius", info);
	}

	if (info.find("attenuation") != std::string::npos) {
		this->attenuationVec = extractVector3D("attenuation", info);
	}

	if (info.find("location") != std::string::npos) {
		this->location = extractVector3D("location", info);
	}
}

x3dPointLight::~x3dPointLight()
{
}

Vector3D x3dPointLight::getAttenuation()
{
	return this->attenuationVec;
}

Vector3D x3dPointLight::getLocation()
{
	return this->location;
}

float x3dPointLight::getRadius()
{
	return this->radius;
}
