#pragma once
#include "x3dShape.h"
class x3dTorus :
	public x3dShape
{
public:
	x3dTorus(int start, std::string infos, int id);
	~x3dTorus();

	float getTorusInnerRadius();
	float getTorusOuterRadius();
	float getTorusAngle();
	float * getSubdivision();

private:

	float torusinnerRadius = 0.5f;
	float torusouterRadius = 1.f;
	float torusangle = TWOPI2;
	//--------
	float subdivision[2] = { 24.f,24.f };
	//--------
};

