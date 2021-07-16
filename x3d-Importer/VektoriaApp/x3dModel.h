/*
Hält und wertet die Informationen einer triangulierten Geometrie aus.
Autor: Lukas Zickl
*/

#pragma once
#include "x3dShape.h"
#include <string>
#include <vector>
#include "Vector3D.h"
#include "Pair.h"
#include <thread>

class x3dModel:public x3dShape
{
public:
	x3dModel(int start, std::string info, int id);
	~x3dModel();

	std::vector<Vector3D> getCoordinates();
	std::vector<Vector3D> getNormalVectors();
	std::vector<Pair<float, float>> getTextureCoordinates();
	std::vector<int> getIndexListVec();

private:

	void createCoordinates();
	void createNormalVectors();
	void createTextureCoordinates();
	void createIndexList();

	std::string geoInfo;

	std::vector<int> indexListVec;
	std::vector<Vector3D> coordinates;
	std::vector<Vector3D> normalVecs;
	std::vector<Pair<float, float>> uvcoords;

	bool getNormalPerVertex();
	bool getColorPerVertex();

	//Parsed-not-Implemented----------
	bool normalPerVertex = true;
	bool colorPerVertex = true;

	//--------------------------------
	std::string temp1 = "";
	std::string temp2 = "";
	std::string temp3 = "";
	int number = 0;
	std::string word = "";
	int count = 0;

};

