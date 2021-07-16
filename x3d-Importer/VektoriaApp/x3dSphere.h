#pragma once
#include "x3dShape.h"
class x3dSphere :
	public x3dShape
{
public:
	x3dSphere(int start, std::string infos, int id);
	~x3dSphere();

	float getSphereRadius();
	float * getSubdivision();

private:


	float sphereradius = 1;

	//----------
	float subdivision[2] { 24, 24 };
};

