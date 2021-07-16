#include "x3dPyramid.h"

x3dPyramid::x3dPyramid(int start, std::string infos, int id)
{
	this->startingLine = start;
	this->specifier = id;
	setGeneral(infos);

	if (infos.find("height") != std::string::npos) {
		this->height = extractFloat("height", infos);
	}
	if (infos.find("xbottom") != std::string::npos) {
		this->xBottom = extractFloat("xbottom", infos);
	}
	if (infos.find("ybottom") != std::string::npos) {
		this->yBottom = extractFloat("ybottom", infos);
	}
	if (infos.find("ytop") != std::string::npos) {
		this->yTop = extractFloat("ytop", infos);
	}
	if (infos.find("xtop") != std::string::npos) {
		this->xTop = extractFloat("xtop", infos);
	}
}

x3dPyramid::~x3dPyramid()
{
}

float x3dPyramid::getHeight()
{
	return this->height;
}

float x3dPyramid::getXBottom()
{
	return this->xBottom;
}

float x3dPyramid::getYBottom()
{
	return this->yBottom;
}

float x3dPyramid::getXTop()
{
	return this->xTop;
}

float x3dPyramid::getYTop()
{
	return this->yTop;
}
