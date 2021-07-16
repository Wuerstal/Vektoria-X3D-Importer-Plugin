#include "x3dRectangularTorus.h"

x3dRectangularTorus::x3dRectangularTorus(int start, std::string infos, int id)
{
	this->startingLine = start;
	this->specifier = id;
	setGeneral(infos);
	
	if (infos.find("height") != std::string::npos) {
		this->height = extractFloat("height", infos);
	}

	if (infos.find("innerradius") != std::string::npos) {
		this->innerRadius = extractFloat("innerradius", infos);
	}

	if (infos.find("outerradius") != std::string::npos) {
		this->outerRadius = extractFloat("outerradius", infos);
	}

	if (infos.find("angle") != std::string::npos) {
		//angle in instplay viewer keine auswirkung
		std::string specificTransformation = infos;
		specificTransformation.erase(std::remove(specificTransformation.begin(), specificTransformation.end(), ' '), specificTransformation.end());
		specificTransformation = specificTransformation.substr(specificTransformation.find("angle=\"") + 7);
		specificTransformation = specificTransformation.substr(0, specificTransformation.find("\"", 0));
		//weitere winkel?
		if (specificTransformation == "twopi")
			this->angle = TWOPI2;
		else if (specificTransformation == "pi")
			this->angle = PI2;
		else
			this->angle = std::stof(specificTransformation);
	}

	if (infos.find("subdivision") != std::string::npos) {
		this->subdivision = extractFloat("subdivision", infos);
	}
	infos.erase(std::remove(infos.begin(), infos.end(), ' '), infos.end());
	if (infos.find("caps=\"false\"") != std::string::npos) {
		this->caps = false;
	}
}

x3dRectangularTorus::~x3dRectangularTorus()
{
}

float x3dRectangularTorus::getAngle()
{
	return this->angle;
}

float x3dRectangularTorus::getHeight()
{
	return this->height;
}

float x3dRectangularTorus::getOuterRadius()
{
	return this->outerRadius;
}

float x3dRectangularTorus::getInnerRadius()
{
	return this->innerRadius;
}

float x3dRectangularTorus::getSubdivision()
{
	return this->subdivision;
}

bool x3dRectangularTorus::getCaps()
{
	return this->caps;
}
