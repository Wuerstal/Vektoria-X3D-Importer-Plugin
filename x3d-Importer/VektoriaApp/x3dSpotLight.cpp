#include "x3dSpotLight.h"

x3dSpotLight::x3dSpotLight(int start, std::string info, int id)
{
	this->specifier = id;
	this->startingLine = start;
	createGeneralParameters(info);

	if (info.find("location") != std::string::npos) {
		this->location = extractVector3D("location", info);
	}
	if (info.find("direction") != std::string::npos) {
		this->direction = extractVector3D("direction", info);
	}

	if (info.find("attenuation") != std::string::npos) {
		this->attenuationVec = extractVector3D("attenuation", info);
	}

	if (info.find("beamwidth") != std::string::npos) {
		this->innerAngle = extractFloat("beamwidth", info);
	}

	if (info.find("cutoffangle") != std::string::npos) {
		this->outerAngle = extractFloat("cutoffangle", info);
	}
	if (info.find("shadowcascades") != std::string::npos) {
		this->shadowCascades = extractFloat("shadowcascades", info);
	}
	if (info.find("shadowsplitfactor") != std::string::npos) {
		this->shadowSplitFactor = extractFloat("shadowsplitfactor", info);
	}
	if (info.find("shadowsplitoffset") != std::string::npos) {
		this->shadowSplitOffset = extractFloat("shadowsplitoffset", info);
	}
}

x3dSpotLight::~x3dSpotLight()
{
}

Vector3D x3dSpotLight::getDirection()
{
	return this->direction;
}

Vector3D x3dSpotLight::getAttenuation()
{
	return this->attenuationVec;
}

Vector3D x3dSpotLight::getLocation()
{
	return this->location;
}

float x3dSpotLight::getInnerAngle()
{
	return this->innerAngle;
}

float x3dSpotLight::getOuterAngle()
{
	return this->outerAngle;
}

float x3dSpotLight::getMaxDist()
{
	return this->maxDist;
}

float x3dSpotLight::getShadowSplitFactor()
{
	return this->shadowSplitFactor;
}

float x3dSpotLight::getShadowSplitOffset()
{
	return this->shadowSplitOffset;
}

int x3dSpotLight::getShadowCascades()
{
	return this->shadowCascades;
}
