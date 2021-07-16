/*
Hält und wertet Informationen aus, die jeder Viewpoint besitzt.
Autor: Lukas Zickl
*/

#pragma once
#include "x3dObject.h"
#include "Vector3D.h"
class x3dView :
	public x3dObject
{
public:
	x3dView(int start, std::string infos, int id);
	x3dView();
	virtual ~x3dView();

	void generateGenerallParameters(std::string infos);

	float getFar();
	float getNear();
	Vector3D getOrientation();
	Vector3D getPosition();
	Vector3D getCenterOfRotation();

private:
	float farPlane = 30000.f;
	float nearPlane = 0.1f;
	Vector3D orientation = Vector3D(0.f, 0.f, 1.f, 0.f);
	Vector3D position = Vector3D(0.f, 0.f, 1.f, 0.f);
	//Parsed-not-Implemented-------------------------
	Vector3D centerOfRotation = Vector3D(0.f, 0.f, 0.f, 0.f);
	bool isActive = false;
	//-----------------------------------------------
};

