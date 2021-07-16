#pragma once
#include "x3dShape.h"
class x3dDish :
	public x3dShape
{
public:
	x3dDish(int start, std::string infos, int id);
	~x3dDish();

	bool getBottom();
	float getDiameter();
	float getHeight();
	float getRadius();
	float * getSubdivision();

private:

	bool bottom = true;
	float diameter = 2;
	float height = 1;
	float radius = 1;
	float subdivision[2] = { 24,24 };

};

