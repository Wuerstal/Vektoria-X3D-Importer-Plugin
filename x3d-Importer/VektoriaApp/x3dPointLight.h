#pragma once
#include "x3dLight.h"
class x3dPointLight :
	public x3dLight
{
public:
	x3dPointLight(int start, std::string info, int id);
	~x3dPointLight();

	Vector3D getAttenuation();
	Vector3D getLocation();
	float getRadius();

private:

	float radius = 100.f;
	Vector3D location = Vector3D(0, 0, 0, 0); 

	//Parsed-Not-Implemented-----------------------
	Vector3D attenuationVec = Vector3D(1, 0, 0, 0); 
	//---------------------------------------------
};

