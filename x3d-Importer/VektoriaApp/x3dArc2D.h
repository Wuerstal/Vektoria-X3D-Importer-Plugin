#pragma once
#include "x3dShape.h"
class x3dArc2D :
	public x3dShape
{
public:
	x3dArc2D(int start, std::string infos, int id);
	~x3dArc2D();

	float getArcRadius();
	float getStartAngle();
	float getEndAngle();
	float getStartAngleInDegree();
	float getEndAngleInDegree();
	float getDegree();

private:
	float arcradius = 1.f;
	float startAngle = 0.f;
	float endAngle = 1.570796f;


	//-------
	float subdivision = 32;
	//-------
};

