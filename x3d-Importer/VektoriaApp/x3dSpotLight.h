#pragma once
#include "x3dLight.h"
class x3dSpotLight :
	public x3dLight
{
public:
	x3dSpotLight(int start, std::string info, int id);
	~x3dSpotLight();

	Vector3D getDirection();
	Vector3D getAttenuation();
	Vector3D getLocation();
	float getInnerAngle();
	float getOuterAngle();
	float getMaxDist();
	float getShadowSplitFactor();
	float getShadowSplitOffset();
	int getShadowCascades();

private:
	Vector3D direction = Vector3D(0.f, 0.f, -1.f, 0.f); 
	Vector3D attenuationVec = Vector3D(1.f, 0.f, 0.f, 0.f); 
	Vector3D location = Vector3D(0.f, 0.f, 0.f, 0.f); 

	float innerAngle = 1.5707963f; //beamWidth
	float outerAngle = 1.5707963f; //cutOffAngle
	float maxDist = 100.f; //radius

	//Parsed-not-Implemented--------
	float shadowSplitFactor = 1.f;
	float shadowSplitOffset = 1.f;
	int shadowCascades = 1.f;
	//------------------------------
};

