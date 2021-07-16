//Autor: Lukas Zickl

#pragma once
#include "x3dView.h"
class x3dOrthoviewpoint :
	public x3dView
{
public:
	x3dOrthoviewpoint(int start, std::string info, int id);
	~x3dOrthoviewpoint();

	Vector3D getFov();
private:
	Vector3D orthoFov = Vector3D(-1, -1, 1, 1);
};

