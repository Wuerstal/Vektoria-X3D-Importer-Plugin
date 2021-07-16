#include "x3dCylinder.h"

x3dCylinder::x3dCylinder(int start, std::string infos, int id)
{
	this->startingLine = start;
	this->specifier = id;
	setGeneral(infos);
	std::string specificTransformation = infos;
	if (specificTransformation.find("radius") != std::string::npos) {
		this->cylinderradius = extractFloat("radius", infos);
	}
	specificTransformation = infos;
	if (specificTransformation.find("height") != std::string::npos) {
		this->cylinderheight = extractFloat("height", infos);
	}
	specificTransformation = infos;
	if (specificTransformation.find("subdivision") != std::string::npos) {
		this->subdivision = extractFloat("subdivision", infos);
	}
}

x3dCylinder::~x3dCylinder()
{
}

float x3dCylinder::getCylinderRadius()
{
	return this->cylinderradius;
}

float x3dCylinder::getCylinderHeight()
{
	return this->cylinderheight;
}

float x3dCylinder::getSubdivision()
{
	return this->subdivision;
}
