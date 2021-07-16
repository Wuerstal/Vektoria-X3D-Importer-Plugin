//Autor: Lukas Zickl

#pragma once
#include "x3dShape.h"
class x3dSnout :
	public x3dShape
{
public:
	x3dSnout(int start, std::string infos, int id);
	~x3dSnout();

	float getDBottom();
	float getHeight();
	float getDTop();
	float getXOff();
	float getYOff();

private:
	float dBottom = 1.0;
	float height = 1.0;
	float dTop = 0.5;
	float xOff = 0.25;
	float yOff = 0.25;

	bool bottom = true;
	bool top = true;
	float subdivision = 32;
};

