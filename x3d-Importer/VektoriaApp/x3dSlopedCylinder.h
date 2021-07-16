//Autor: Lukas Zickl

#pragma once
#include "x3dShape.h"
class x3dSlopedCylinder :
	public x3dShape
{
public:
	x3dSlopedCylinder(int start, std::string infos, int id);
	~x3dSlopedCylinder();

	float getHeight();
	float getRadius();
	float getXBShear();
	float getXTShear();
	float getYBShear();
	float getYTShear();
	float getSubdivision();
	bool getBottom();
	bool getTop();

private:

	float height = 2.f;
	float radius = 1.f;
	float xbshear = 0.26179f;
	float xtshear = 0.26179f;
	float ybshear = 0.f;
	float ytshear = 0.f;


	//--------------
	float subdivision = 32.f;
	bool bottom = true;
	bool top = true;
	//--------------
};

