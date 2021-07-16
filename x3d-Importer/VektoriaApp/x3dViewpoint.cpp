#include "x3dViewpoint.h"

x3dViewpoint::x3dViewpoint(int start, std::string info, int id)
{
	this->specifier = id;
	this->startingLine = start;
	generateGenerallParameters(info);

	if (info.find("fieldofview") != std::string::npos) {
		this->fov = extractFloat("fieldofview", info);
	}
}

x3dViewpoint::~x3dViewpoint()
{
}

float x3dViewpoint::getFov()
{
	return this->fov;
}

