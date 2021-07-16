//Autor: Lukas Zickl

#pragma once
#include "x3dShape.h"
class x3dDisk2D :
	public x3dShape
{
public:
	x3dDisk2D(int start, std::string infos, int id);
	~x3dDisk2D();

	float getDiskInnerRadius();
	float getDiskOuterRadius();

private:

	float diskinnerRadius = 0.f;
	float diskouterRadius = 1.f;
};

