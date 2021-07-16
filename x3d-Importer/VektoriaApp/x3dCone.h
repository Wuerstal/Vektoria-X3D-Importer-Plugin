#pragma once
#include "x3dShape.h"
class x3dCone :
	public x3dShape
{
public:
	x3dCone(int start, std::string infos, int id);
	~x3dCone();

	float getConeHeight();
	float getConeBottomRadius();
	float getConeTopRadius();
	float getSubdivision();

private:

	float coneheight = 2.f;
	float conebottomradius = 1.f;
	float conetopradius = 0.0f;

	//---------
	float subdivision = 32;
	//---------
};

