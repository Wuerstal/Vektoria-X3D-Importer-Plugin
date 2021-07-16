#include "x3dArc2D.h"

x3dArc2D::x3dArc2D(int start, std::string infos, int id)
{
	this->startingLine = start;
	this->specifier = id;
	setGeneral(infos);
	if (infos.find("radius") != std::string::npos) {
		this->arcradius = extractFloat("radius", infos);
	}
	if (infos.find("endangle") != std::string::npos) {
		this->endAngle = extractFloat("endangle", infos);
	}
	if (infos.find("startangle") != std::string::npos) {
		this->startAngle = extractFloat("startangle", infos);
	}
	if (infos.find("subdivision") != std::string::npos) {
		this->subdivision = extractFloat("subdivision", infos);
	}
}

x3dArc2D::~x3dArc2D()
{
}


float x3dArc2D::getArcRadius()
{
	return this->arcradius;
}

float x3dArc2D::getStartAngle()
{
	return this->startAngle;
}

float x3dArc2D::getEndAngle()
{
	return this->endAngle;
}

float x3dArc2D::getStartAngleInDegree()
{
	return this->startAngle * 180 / PI2;
}

float x3dArc2D::getEndAngleInDegree()
{
	return this->endAngle * 180 / PI2;
}

float x3dArc2D::getDegree()
{
	float deg = this->getEndAngleInDegree() - this->getStartAngleInDegree();
	return deg;
}
