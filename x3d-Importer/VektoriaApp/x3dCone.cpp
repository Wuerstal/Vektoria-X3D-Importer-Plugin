#include "x3dCone.h"

x3dCone::x3dCone(int start, std::string infos, int id)
{
	this->startingLine = start;
	this->specifier = id;
	setGeneral(infos);

	
	if (infos.find("height") != std::string::npos) {
		this->coneheight = extractFloat("height", infos);
	}
	if (infos.find("bottomradius") != std::string::npos) {
		this->conebottomradius = extractFloat("bottomradius", infos);
	}
	if (infos.find("topradius") != std::string::npos) {
		this->conetopradius = extractFloat("topradius", infos);
	}
	if (infos.find("subdivision") != std::string::npos) {
		this->subdivision = extractFloat("subdivision", infos);
	}
}

x3dCone::~x3dCone()
{
}

float x3dCone::getConeHeight()
{
	return this->coneheight;
}

float x3dCone::getConeBottomRadius()
{
	return this->conebottomradius;
}

float x3dCone::getConeTopRadius()
{
	return this->conetopradius;
}

float x3dCone::getSubdivision()
{
	return this->subdivision;
}
