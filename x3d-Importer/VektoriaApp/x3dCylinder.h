#pragma once
#include "x3dShape.h"
class x3dCylinder :
	public x3dShape
{
public:
	x3dCylinder(int start, std::string infos, int id);
	~x3dCylinder();

	float getCylinderRadius();
	float getCylinderHeight();
	float getSubdivision();

private:

	float cylinderradius = 1;
	float cylinderheight = 2;
	//----------
	float subdivision = 32;
	//----------
};

