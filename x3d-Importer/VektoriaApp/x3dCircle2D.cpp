#include "x3dCircle2D.h"

x3dCircle2D::x3dCircle2D(int start, std::string infos, int id)
{
	std::string specificTransformation = infos;
	this->startingLine = start;
	this->specifier = id;
	setGeneral(infos);
	if (specificTransformation.find("radius") != std::string::npos) {
		
		this->circleradius = extractFloat("radius", infos);
	}
}

x3dCircle2D::~x3dCircle2D()
{
}

float x3dCircle2D::getCircleRadius()
{
	return this->circleradius;
}
