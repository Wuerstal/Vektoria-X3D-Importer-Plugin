#include "x3dSphere.h"

x3dSphere::x3dSphere(int start, std::string infos, int id)
{
	this->startingLine = start;
	this->specifier = id;
	setGeneral(infos);

	if (infos.find("radius") != std::string::npos) {
		this->sphereradius = extractFloat("radius", infos);
	}
	if (infos.find("subdivision") != std::string::npos) {
		std::array<float, 2> t = extractFloatArray2("subdivision", infos);
		this->subdivision[0] = t[0];
		this->subdivision[1] = t[1];
	}
}

x3dSphere::~x3dSphere()
{
}

float x3dSphere::getSphereRadius()
{
	return this->sphereradius;
}

float * x3dSphere::getSubdivision()
{
	return this->subdivision;
}
