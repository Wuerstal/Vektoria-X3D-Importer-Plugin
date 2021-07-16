#include "x3dDish.h"

x3dDish::x3dDish(int start, std::string infos, int id)
{
	this->startingLine = start;
	this->specifier = id;
	setGeneral(infos);
	std::string specificTransformation = infos;
	if (specificTransformation.find("subdivision") != std::string::npos) {
		std::array<float,2> t = extractFloatArray2("size", infos);
		this->subdivision[0] = t[0];
		this->subdivision[1] = t[1];
	}
	specificTransformation = infos;
	if (specificTransformation.find("diameter") != std::string::npos) {
		this->diameter = extractFloat("diameter", infos);
		this->radius = this->diameter / 2;
	}
	specificTransformation = infos;
	if (specificTransformation.find("height") != std::string::npos) {
		this->height = extractFloat("height", infos);
	}
	infos.erase(std::remove(infos.begin(), infos.end(), ' '), infos.end());
	if (infos.find("bottom=\"false\"") != std::string::npos) {
		this->bottom = false;
	}

}

x3dDish::~x3dDish()
{
}

bool x3dDish::getBottom()
{
	return this->bottom;
}

float x3dDish::getDiameter()
{
	return 0.0f;
}

float x3dDish::getHeight()
{
	return this->height;
}

float x3dDish::getRadius()
{
	return this->radius;
}

float * x3dDish::getSubdivision()
{
	return this->subdivision;
}
