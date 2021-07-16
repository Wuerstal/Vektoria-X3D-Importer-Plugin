#pragma once
#include "x3dView.h"
#include <string>

class x3dViewpoint:public x3dView
{
public:
	x3dViewpoint(int start, std::string info, int id);
	~x3dViewpoint();

	float getFov();

private:
	float fov = 0.785398f;

};

