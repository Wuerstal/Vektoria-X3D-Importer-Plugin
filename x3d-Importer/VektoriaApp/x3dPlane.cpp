#include "x3dPlane.h"

x3dPlane::x3dPlane(int start, std::string infos, int id)
{
	this->startingLine = start;
	this->specifier = id;
	setGeneral(infos);
	std::string specificTransformation = infos;
	if (specificTransformation.find("size") != std::string::npos) {
		std::array<float, 2> t = extractFloatArray2("size", infos);
		this->planesize[0] = t[0] / 2;
		this->planesize[1] = t[1] / 2;
		
	}
	specificTransformation = infos;
	if (specificTransformation.find("center") != std::string::npos) {
		std::array<float, 2> t = extractFloatArray2("center", infos);
		this->planecenter[0] = t[0] / 2;
		this->planecenter[1] = t[1] / 2;
	}
	if (specificTransformation.find("subdivision") != std::string::npos) {
		std::array<float, 2> t = extractFloatArray2("subdivision", infos);
		this->subdivision[0] = t[0];
		this->subdivision[1] = t[1];
	}
}

x3dPlane::~x3dPlane()
{
}

float * x3dPlane::getPlaneSize()
{
	return this->planesize;
}

float * x3dPlane::getPlaneCenter()
{
	return this->planecenter;
}

float * x3dPlane::getSubdivision()
{
	return this->subdivision;
}
