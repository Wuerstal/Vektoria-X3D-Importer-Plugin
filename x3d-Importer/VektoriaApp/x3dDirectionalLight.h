//Autor: Lukas Zickl

#pragma once
#include "x3dLight.h"
class x3dDirectionalLight :
	public x3dLight
{
public:
	x3dDirectionalLight(int start, std::string info, int id);
	~x3dDirectionalLight();

	Vector3D getDirection();
	float getShadowSplitFactor();
	float getShadowSplitOffset();
	int getShadowCascades();

private:
	Vector3D direction = Vector3D(0, 0, -1, 0);

	//Parsed-not-Implemented--------
	float shadowSplitFactor = 1;
	float shadowSplitOffset = 1;
	int shadowCascades = 1;
	//------------------------------
};

