#include "x3dDisk2D.h"

x3dDisk2D::x3dDisk2D(int start, std::string infos, int id)
{
	this->startingLine = start;
	this->specifier = id;
	setGeneral(infos);
	if (infos.find("innerradius") != std::string::npos) {
		this->diskinnerRadius = extractFloat("innerradius", infos);;
	}
	if (infos.find("outerradius") != std::string::npos) {
		this->diskouterRadius = extractFloat("outerradius", infos);
	}
}

x3dDisk2D::~x3dDisk2D()
{
}

float x3dDisk2D::getDiskInnerRadius()
{
	return this->diskinnerRadius;
}

float x3dDisk2D::getDiskOuterRadius()
{
	return this->diskouterRadius;
}
