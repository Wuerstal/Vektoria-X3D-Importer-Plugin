/*
Wertet und hält Informationen die jede Geometrie besitzt aus.
*/

#pragma once
#include "Appearance.h"
#include "x3dObject.h"
#define TWOPI2 6.2831853071 
#define PI2 3.14159265358

//TODO: Shapes that are not visible in x3dviewer parsing

class x3dShape : public x3dObject
{
public:
	x3dShape(int start, std::string infos, int id);
	x3dShape();
	virtual ~x3dShape();
	
	void setAppearance(Appearance appear);
	void setGeneral(std::string infos);
	bool getHasAppearance();
	Appearance getAppearance();

protected:
	
	Appearance appearance;
	bool hasAppearance = false;

	//Parsed not implemented
	bool lit = true;
	bool solid = true;
	bool useGeoCache = true;
	bool ccw = true;
	//-----------------------



	/*--------------
	MISSING-Features
	- boundingBoxCenter
	- BoundingBoxSize
	- isPickable
	- render
	--------------*/

};

