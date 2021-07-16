/*
Mutterklasse für Objekte. Enthält Zeilenzahl für Start und End-Tag, die Objekt ID und die Transformationsmatirx des Objektes.
Autor: Lukas Zickl
*/

#pragma once
#include <string>
#include "Matrix.h"
#include "Vector3D.h"
class x3dObject
{
public:
	x3dObject(int start, std::string infos, int id);
	x3dObject();
	virtual ~x3dObject();

	int getEndingLine();
	int getStartingLine();
	int getSpecifier();
	virtual void setEndingLine(int end);
	virtual void setTransformations(std::array<float, 16> mat);
	std::array<float, 16> getMatrix();

	static float extractFloat(std::string lookFor, std::string infos);
	static int extractInt(std::string lookFor, std::string infos);
	static std::string extractString(std::string lookFor, std::string infos);
	static std::array<float, 3> extractFloatArray3(std::string lookFor, std::string infos);
	static std::array<float, 2> extractFloatArray2(std::string lookFor, std::string infos);
	static Vector3D extractVector3D(std::string lookFor, std::string infos);

protected:
	int specifier = 0;	 //0=IndexedTriangleList, 1=PointSet
						 //100=Box, 101=Sphere, 102=Cone, 103=Circle2D, 104=arc2D, 105=ArcClose2D, 106=Cylinder, 107=Disk, 108=Plane/Rectangle
						 //109=Pyramid, 110=Torus, 111=Dish, 112=RectangularTorus, 113=SlopedCylinder, 114=Snout, 115=SphereSegment
					     //200=pointlight, 201=spotlight, 202=directionalLight
						 //300=Viewpoint, 301=OrthoViewPoint
						 //400=Text
	int endingLine = 0;
	int startingLine = 0;
	std::array<float, 16> matrix = { 1,0,0,0,
									 0,1,0,0,
									 0,0,1,0,
									 0,0,0,1 };
	bool matrixSet = false;
};

