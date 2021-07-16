#pragma once
#include "x3dShape.h"
class x3dSphereSegment :
	public x3dShape
{
public:
	x3dSphereSegment(int start, std::string infos, int id);
	~x3dSphereSegment();

	float getRadius();
	float * getStepSize();
	std::vector<float> getLatitude();
	std::vector<float> getLongitude();

private:

	std::vector<float> latitude;
	std::vector<float> longitude;
	float radius = 1;
	float stepSize[2] = { 1,1 };
};

