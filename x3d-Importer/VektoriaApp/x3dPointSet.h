#pragma once
#include "x3dShape.h"
class x3dPointSet :
	public x3dShape
{
public:
	x3dPointSet(int start, std::string info, int id);
	~x3dPointSet();

	std::vector<Vector3D> getCoords();
	Vector3D getColor();

private:

	std::vector<Vector3D> coords;
	std::string geoInfo;

	//--------
	Vector3D color = Vector3D(0, 0, 0, 0);
	//--------
};

