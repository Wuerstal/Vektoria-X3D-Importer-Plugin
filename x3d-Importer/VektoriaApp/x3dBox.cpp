#include "x3dBox.h"

x3dBox::x3dBox(int start, std::string infos, int id)
{
	this->startingLine = start;
	this->specifier = id;
	setGeneral(infos);
	std::string specificTransformation = infos;
	if (specificTransformation.find("size") != std::string::npos) {
		std::array<float,3> t = extractFloatArray3("size", infos);
		this->boxsize[0] = t[0]/2;
		this->boxsize[1] = t[1]/2;
		this->boxsize[2] = t[2]/2;
	}
}

x3dBox::~x3dBox()
{
}

float * x3dBox::getBoxSize()
{
	return this->boxsize;
}
