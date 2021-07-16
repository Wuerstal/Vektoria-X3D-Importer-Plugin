#include "x3dArcClose2D.h"

x3dArcClose2D::x3dArcClose2D(int start, std::string infos, int id)
{
	this->startingLine = start;
	this->specifier = id;
	setGeneral(infos);
	if (infos.find("radius") != std::string::npos) {
		this->arcclosedradius = extractFloat("radius", infos);
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

x3dArcClose2D::~x3dArcClose2D()
{
}

float x3dArcClose2D::getArcClosedRadius()
{
	return this->arcclosedradius;
}

float x3dArcClose2D::getStartAngle()
{
	return this->startAngle;
}

float x3dArcClose2D::getEndAngle()
{
	return this->endAngle;
}

float x3dArcClose2D::getStartAngleInDegree()
{
	return this->startAngle*180/PI2;
}

float x3dArcClose2D::getEndAngleInDegree()
{
	return this->endAngle*180/PI2;
}

float x3dArcClose2D::getDegree()
{
	float deg = this->getEndAngleInDegree() - this->getStartAngleInDegree();
	return deg;
}
