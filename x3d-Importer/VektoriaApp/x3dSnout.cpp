#include "x3dSnout.h"

x3dSnout::x3dSnout(int start, std::string infos, int id)
{
	this->startingLine = start;
	this->specifier = id;
	setGeneral(infos);
	std::string specificTransformation = infos;
	if (infos.find("subdivision") != std::string::npos) {
		this->subdivision = extractFloat("subdivision", infos);
	}

	if (infos.find("height") != std::string::npos) {
		this->height = extractFloat("height", infos);
	}

	if (infos.find("dbottom") != std::string::npos) {
		this->dBottom = extractFloat("dbottom", infos);
	}
	
	if (infos.find("dtop") != std::string::npos) {
		this->dTop = extractFloat("dtop", infos);
	}

	if (infos.find("xoff") != std::string::npos) {
		this->xOff = extractFloat("xoff", infos);
	}

	if (infos.find("yoff") != std::string::npos) {
		this->yOff = extractFloat("yoff", infos);
	}
	infos.erase(std::remove(infos.begin(), infos.end(), ' '), infos.end());
	if (infos.find("bottom=\"false\"") != std::string::npos) {
		this->bottom = false;
	}
	if (infos.find("top=\"false\"") != std::string::npos) {
		this->bottom = false;
	}
}

x3dSnout::~x3dSnout()
{
}

float x3dSnout::getDBottom()
{
	return this->dBottom;
}

float x3dSnout::getHeight()
{
	return this->height;
}

float x3dSnout::getDTop()
{
	return this->dTop;
}

float x3dSnout::getXOff()
{
	return this->xOff;
}

float x3dSnout::getYOff()
{
	return this->yOff;
}
