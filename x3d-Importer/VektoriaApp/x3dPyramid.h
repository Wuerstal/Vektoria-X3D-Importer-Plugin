//Autor: Lukas Zickl

#pragma once
#include "x3dShape.h"
class x3dPyramid :
	public x3dShape
{
public:
	x3dPyramid(int start, std::string infos, int id);
	~x3dPyramid();

	float getHeight();
	float getXBottom();
	float getYBottom();
	float getXTop();
	float getYTop();

private:
	float height = 1;
	float xBottom = 1;
	float yBottom = 1;
	float xTop = 0;
	float yTop = 0;

	//------------
	float xOff = 0.25;
	float yOff = 0.25;
	//------------

};

