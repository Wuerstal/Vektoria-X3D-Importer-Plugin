#include "x3dTorus.h"

x3dTorus::x3dTorus(int start, std::string infos, int id)
{

	this->startingLine = start;
	this->specifier = id;
	setGeneral(infos);

	if (infos.find("innerradius") != std::string::npos) {
		this->torusinnerRadius = extractFloat("innerradius", infos);
	}
	if (infos.find("outerradius") != std::string::npos) {
		this->torusouterRadius = extractFloat("outerradius", infos);
	}
	if (infos.find("angle") != std::string::npos) {
		std::string specificTransformation = infos;
		specificTransformation.erase(std::remove(specificTransformation.begin(), specificTransformation.end(), ' '), specificTransformation.end());
		specificTransformation = specificTransformation.substr(specificTransformation.find("angle=\"") + 7);
		specificTransformation = specificTransformation.substr(0, specificTransformation.find("\"", 0));
		//weitere winkel?
		if (specificTransformation == "twopi")
			this->torusangle = TWOPI2;
		else if (specificTransformation == "pi")
			this->torusangle = PI2;
		else
			this->torusangle = std::stof(specificTransformation);
	}
	if (infos.find("subdivision") != std::string::npos) {
		std::array<float, 2> t = extractFloatArray2("subdivision", infos);
		this->subdivision[0] = t[0];
		this->subdivision[1] = t[1];
	}
}

x3dTorus::~x3dTorus()
{
}

float x3dTorus::getTorusInnerRadius()
{
	return this->torusinnerRadius;
}

float x3dTorus::getTorusOuterRadius()
{
	return this->torusouterRadius;
}

float x3dTorus::getTorusAngle()
{
	return this->torusangle;
}

float * x3dTorus::getSubdivision()
{
	return this->subdivision;
}
