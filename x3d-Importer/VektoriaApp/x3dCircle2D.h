//Autor: Lukas Zickl

#pragma once
#include "x3dShape.h"
class x3dCircle2D :
	public x3dShape
{
public:
	x3dCircle2D(int start, std::string infos, int id);
	~x3dCircle2D();

	float getCircleRadius();

private:

	float circleradius = 1;
};

