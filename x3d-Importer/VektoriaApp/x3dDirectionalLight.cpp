#include "x3dDirectionalLight.h"

x3dDirectionalLight::x3dDirectionalLight(int start, std::string info, int id)
{
	this->specifier = id;
	this->startingLine = start;
	createGeneralParameters(info);
	std::string specificInfos = info;

	if (info.find("direction") != std::string::npos) {
		this->direction = extractVector3D("direction", info);
	}
	if (info.find("shadowcascades") != std::string::npos) {
		this->shadowCascades = extractInt("shadowcascades", info);
	}
	if (info.find("shadowsplitfactor") != std::string::npos) {
		this->shadowSplitFactor = extractFloat("shadowsplitfactor", info);
	}
	if (info.find("shadowsplitoffset") != std::string::npos) {
		this->shadowSplitOffset = extractFloat("shadowsplitoffset", info);
	}
}

x3dDirectionalLight::~x3dDirectionalLight()
{
}

Vector3D x3dDirectionalLight::getDirection()
{
	return this->direction;
}

float x3dDirectionalLight::getShadowSplitFactor()
{
	return this->shadowSplitFactor;
}

float x3dDirectionalLight::getShadowSplitOffset()
{
	return this->shadowSplitOffset;
}

int x3dDirectionalLight::getShadowCascades()
{
	return this->shadowCascades;
}
