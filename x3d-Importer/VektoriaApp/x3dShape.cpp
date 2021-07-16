#include "x3dShape.h"


x3dShape::x3dShape(int start, std::string infos, int id)
{
}

x3dShape::x3dShape()
{
}

x3dShape::~x3dShape()
{
}

void x3dShape::setAppearance(Appearance appear)
{
	this->appearance = appear;
	this->hasAppearance = true;
}

void x3dShape::setGeneral(std::string infos)
{
	infos.erase(std::remove(infos.begin(), infos.end(), ' '), infos.end());
	if (infos.find("ccw=\"false\"") != std::string::npos) {
		this->ccw = false;
	}
	if (infos.find("lit=\"false\"") != std::string::npos) {
		this->lit = false;
	}
	if (infos.find("solid=\"false\"") != std::string::npos) {
		this->solid = false;
	}
	if (infos.find("usegeocache=\"false\"") != std::string::npos) {
		this->useGeoCache = false;
	}
}

bool x3dShape::getHasAppearance()
{
	return this->hasAppearance;
}

Appearance x3dShape::getAppearance()
{
	return this->appearance;
}


