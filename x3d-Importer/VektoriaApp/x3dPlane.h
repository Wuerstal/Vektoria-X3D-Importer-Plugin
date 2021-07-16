#pragma once
#include "x3dShape.h"
class x3dPlane :
	public x3dShape
{
public:
	x3dPlane(int start, std::string infos, int id);
	~x3dPlane();

	float * getPlaneSize();
	float * getPlaneCenter();
	float * getSubdivision();

private:

	float planesize[2] = { 1, 1 };
	float planecenter[3] = { 0,0,0 };
	//----------
	float subdivision[2] = { 1,1 };
	//----------
};

