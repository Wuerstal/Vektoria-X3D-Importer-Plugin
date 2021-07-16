#include "x3dSlopedCylinder.h"

x3dSlopedCylinder::x3dSlopedCylinder(int start, std::string infos, int id)
{
	this->startingLine = start;
	this->specifier = id;
	setGeneral(infos);
	std::string specificTransformation = infos;

	if (infos.find("subdivision") != std::string::npos) {
		this->subdivision = extractFloat("subdivision", infos);
	}
	if (infos.find("height") != std::string::npos) {
		this->height = extractFloat("height", infos);
	}
	if (infos.find("radius") != std::string::npos) {
		this->radius = extractFloat("radius", infos);
	}
	if (infos.find("xbshear") != std::string::npos) {
		this->xbshear = extractFloat("xbshear", infos);
	}
	if (infos.find("xtshear") != std::string::npos) {
		this->xtshear = extractFloat("xtshear", infos);
	}
	if (infos.find("ytshear") != std::string::npos) {
		this->ytshear = extractFloat("ytshear", infos);
	}
	if (infos.find("ybshear") != std::string::npos) {
		this->ybshear = extractFloat("ybshear", infos);
	}
	infos.erase(std::remove(infos.begin(), infos.end(), ' '), infos.end());
	if (infos.find("bottom=\"false\"") != std::string::npos) {
		this->bottom = false;
	}
	if (infos.find("top=\"false\"") != std::string::npos) {
		this->top = false;
	}

}

x3dSlopedCylinder::~x3dSlopedCylinder()
{
}

float x3dSlopedCylinder::getHeight()
{
	return this->height;
}

float x3dSlopedCylinder::getRadius()
{
	return this->radius;
}

float x3dSlopedCylinder::getXBShear()
{
	return this->xbshear;
}

float x3dSlopedCylinder::getXTShear()
{
	return this->xtshear;
}

float x3dSlopedCylinder::getYBShear()
{
	return this->ybshear;
}

float x3dSlopedCylinder::getYTShear()
{
	return this->ytshear;
}

float x3dSlopedCylinder::getSubdivision()
{
	return this->subdivision;
}

bool x3dSlopedCylinder::getBottom()
{
	return this->bottom;
}

bool x3dSlopedCylinder::getTop()
{
	return this->top;
}
