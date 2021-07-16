/*
Klasse für Informationen, die alle Lichter des x3d-Formates betreffen.
*/

#pragma once
#include "x3dObject.h"

class x3dLight : public x3dObject
{
public:
	x3dLight(int start, std::string info, int id);
	x3dLight();
	virtual ~x3dLight();

	Vector3D getColor();
	float getIntensity();
	float getAmbientIntensity();
	bool getOn();
	int getShadowMapSize();
	bool getGlobal();
	int getShadowFilterSize();
	float getShadowIntensity();
	float getShadowOffset();
	float getZFar();
	float getZNear();

protected:
	void createGeneralParameters(std::string info);
	void parseShadowParameters();

private:

	//Generall
	bool on = true;
	Vector3D lightColor = Vector3D(1,1,1,0);
	float intensity = 1.f;
	int shadowMapSize = 1024;

	//Parsed-not-Implemented-----------
	float ambientIntensity = 0.f;
	bool global = false;
	int shadowFilterSize = 0;
	float shadowIntensity = 0;
	float shadowOffset = 0;
	float zFar = -1;
	float zNear = -1;
	//---------------------------------

};

