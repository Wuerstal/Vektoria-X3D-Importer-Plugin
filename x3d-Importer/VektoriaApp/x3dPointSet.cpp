#include "x3dPointSet.h"

x3dPointSet::x3dPointSet(int start, std::string info, int id)
{
	this->startingLine = start;
	this->geoInfo = info;
	this->specifier = id;
	setGeneral(info);

	std::string coords = this->geoInfo.substr(geoInfo.find("<coordinate point=") + 19);
	coords = coords.substr(0, coords.find('\"'));

	int pos = 0;
	std::vector<std::string> coordStringVecs;
	while ((pos = coords.find(' ')) != std::string::npos) {
		coordStringVecs.emplace_back(coords.substr(0, pos));
		coords.erase(0, pos + 1);
	}
	if (coords.empty() == false) {
		coordStringVecs.emplace_back(coords.substr(0, pos));
	}
	Vector3D vec = Vector3D(0, 0, 0, 1);

	for (int j = 0; j < coordStringVecs.size(); j += 3) {
		vec.x = std::stof(coordStringVecs[j]);
		vec.y = std::stof(coordStringVecs[j + 1]);
		vec.z = std::stof(coordStringVecs[j + 2]);

		this->coords.emplace_back(vec);
	}
}

x3dPointSet::~x3dPointSet()
{
}

std::vector<Vector3D> x3dPointSet::getCoords()
{
	return this->coords;
}

Vector3D x3dPointSet::getColor()
{
	return this->color;
}
