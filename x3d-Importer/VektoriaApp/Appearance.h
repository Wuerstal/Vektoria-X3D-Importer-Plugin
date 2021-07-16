/*
Hält und wertet Informationen für das aussehen einer Geometrie aus.
*/

#pragma once
#include <string>
#include "Vector3D.h"
#include "x3dMaterial.h"
#include "x3dTexture.h"

class Appearance
{
public:
	Appearance(int start, int end, std::string info, std::vector<Pair<std::string, std::string>> &textureDef, std::vector<Pair<std::string, x3dMaterial*>> &materialDef, bool downloadTexture);
	Appearance(); 
	~Appearance();


	int getStartingLine();
	int getEndingLine();
	bool getMaskR();
	bool getMaskG();
	bool getMaskB();
	bool getMaskA();
	x3dMaterial getMaterial();
	x3dTexture getTexture();

private:
	void setColorMasking();
	void setLineProperties();

	int startingLine = 0;
	int endingLine = 0;
	std::string infos;

	x3dMaterial* material;
	x3dTexture* texture;


	//Parsed-not-Implemented-Features-----------

	//alphaClipThreshold
	float alphaClipThreshold = 1;
	//Colormasking
	bool colorMasking = false;
	bool maskR = true;
	bool maskG = true;
	bool maskB = true;
	bool maskA = true;
	//LineProperties
	bool applied = true;
	int lineType = 1;
	float lineWidthScaleFactor = 0;
	//Sorting
	int sortKey = 0;
	std::string sortType = "auto";

	//-----------------------------------------

	/*--------------
	MISSING-Features
	- BlendMode
	- DepthMode
	- Shaders
	- TextureTransform <- Implement!
	--------------*/
};

