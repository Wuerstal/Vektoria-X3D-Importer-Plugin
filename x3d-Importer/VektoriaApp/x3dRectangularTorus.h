//Autor: Lukas Zickl

#pragma once
#include "x3dShape.h"
class x3dRectangularTorus :
	public x3dShape
{
public:
	x3dRectangularTorus(int start, std::string infos, int id);
	~x3dRectangularTorus();

	float getAngle();
	float getHeight();
	float getOuterRadius();
	float getInnerRadius();
	float getSubdivision();
	bool getCaps();

private:
	float height = 1.f;
	float outerRadius = 1.f;
	float innerRadius = 0.5f;
	float subdivision = 32.f;

	//----------
	bool caps = true;
	float angle = PI2;
	//----------
};

