#pragma once
#include "x3dShape.h"
class x3dArcClose2D:public x3dShape
{
public:
	x3dArcClose2D(int start, std::string infos, int id);
	~x3dArcClose2D();

	float getArcClosedRadius();
	float getStartAngle();
	float getEndAngle();
	float getStartAngleInDegree();
	float getEndAngleInDegree();
	float getDegree();

private:

	float arcclosedradius = 1.f;
	float startAngle = 0.f;
	float endAngle = 1.570796f;


	//-------------------
	float subdivision = 32;
	//-------------------
};


