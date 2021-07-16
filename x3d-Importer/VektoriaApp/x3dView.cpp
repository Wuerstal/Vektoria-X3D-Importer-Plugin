#include "x3dView.h"

x3dView::x3dView(int start, std::string infos, int id)
{
	
}

x3dView::x3dView()
{
}

x3dView::~x3dView()
{
}

void x3dView::generateGenerallParameters(std::string infos)
{
	if (infos.find("centerofrotation") != std::string::npos) {
		this->centerOfRotation = extractVector3D("centerofrotation", infos);
	}

	if (infos.find("orientation") != std::string::npos) {
		this->orientation = extractVector3D("orientation", infos);
	}

	if (infos.find("position") != std::string::npos) {
		this->position = extractVector3D("position", infos);
	}

	if (infos.find("zfar") != std::string::npos) {
		this->farPlane = extractFloat("zfar", infos);
	}

	if (infos.find("znear") != std::string::npos) {
		this->nearPlane = extractFloat("znear", infos);
	}
	infos.erase(std::remove(infos.begin(), infos.end(), ' '), infos.end());
	if (infos.find("isactive=\"true\"") != std::string::npos) {
		this->isActive = true;
	}
}

float x3dView::getFar()
{
	return this->farPlane;
}

float x3dView::getNear()
{
	return this->nearPlane;
}

Vector3D x3dView::getOrientation()
{
	return this->orientation;
}

Vector3D x3dView::getPosition()
{
	return this->position;
}

Vector3D x3dView::getCenterOfRotation()
{
	return this->centerOfRotation;
}
