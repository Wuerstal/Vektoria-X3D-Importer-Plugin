#include "x3dModel.h"
#include <thread>
#include <sstream>



x3dModel::x3dModel(int start, std::string info, int id)
{
	this->startingLine = start;
	this->geoInfo = info;
	this->specifier = id;
	setGeneral(info);

	if (true) {

		std::thread t1, t2, t3;
		if (this->geoInfo.find("<coordinate point") != std::string::npos) {
			t1 = std::thread(&x3dModel::createCoordinates, this);
			t2 = std::thread(&x3dModel::createIndexList, this);
		}
		if (this->geoInfo.find("<normal vector") != std::string::npos)
			t3 = std::thread(&x3dModel::createNormalVectors, this);

		if (this->geoInfo.find("<texturecoordinate") != std::string::npos)
			createTextureCoordinates();

		if (this->geoInfo.find("normalpervertex=\"false\"") != std::string::npos) 
			this->normalPerVertex = false;
		
		if (this->geoInfo.find("colorpervertex=\"false\"") != std::string::npos) {
			this->colorPerVertex = false;
		}
		t1.join();
		t2.join();
		t3.join();
	}
	this->geoInfo = "";
}

x3dModel::~x3dModel()
{
}


void x3dModel::createCoordinates()
{
	std::string coords = this->geoInfo.substr(geoInfo.find("<coordinate point=") +19);
	coords = coords.substr(0, coords.find('\"'));

	std::stringstream ss(coords);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);

	Vector3D vec = Vector3D(0, 0, 0, 1);
	
	for (signed int j = 0; j < vstrings.size(); j += 3) {
		vec.x = std::stof(vstrings[j]);
		vec.y = std::stof(vstrings[j + 1]);
		vec.z = std::stof(vstrings[j + 2]);

		this->coordinates.emplace_back(vec);
	}
	ss.str(std::string());
	vstrings.clear();
	vstrings.shrink_to_fit();
}

void x3dModel::createNormalVectors()
{
	std::string normals = this->geoInfo.substr(geoInfo.find("<normal vector=") + 16);
	normals = normals.substr(0, normals.find('\"'));
	
	std::stringstream ss(normals);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);

	Vector3D vecTempNorm = Vector3D(0, 0, 0, 1);

	for (int j = 0; j < vstrings.size(); j += 3) {
		vecTempNorm.x = std::stof(vstrings[j]);
		vecTempNorm.y = std::stof(vstrings[j+1]);
		vecTempNorm.z = std::stof(vstrings[j+2]);

		this->normalVecs.emplace_back(vecTempNorm);
	}
	ss.str(std::string());
	vstrings.clear();
	vstrings.shrink_to_fit();
}

void x3dModel::createTextureCoordinates()
{
	std::string coordsTex = this->geoInfo.substr(geoInfo.find("<texturecoordinate point=") + 26);
	coordsTex = coordsTex.substr(0, coordsTex.find('\"'));

	std::stringstream ss(coordsTex);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);

	Pair<float, float> tempPair;

	for (int i = 0; i < vstrings.size(); i+=2){
		tempPair.setAB(std::stof(vstrings[i]), 1 - std::stof(vstrings[i + 1]));
		this->uvcoords.emplace_back(tempPair);
	}
	ss.str(std::string());
	vstrings.clear();
	vstrings.shrink_to_fit();
}

void x3dModel::createIndexList()
{
	std::string indexList = this->geoInfo.substr(geoInfo.find("index=") + 7);
	indexList = indexList.substr(0, indexList.find('\"'));

	std::stringstream ss(indexList);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);

	for (int i = 0; i < vstrings.size(); i++) {
		this->indexListVec.emplace_back(std::stof(vstrings[i]));
	}
	ss.str(std::string());
	vstrings.clear();
	vstrings.shrink_to_fit();
}

bool x3dModel::getNormalPerVertex()
{
	return this->normalPerVertex;
}

bool x3dModel::getColorPerVertex()
{
	return this->colorPerVertex;
}

std::vector<Vector3D> x3dModel::getCoordinates()
{
	return this->coordinates;
}

std::vector<Vector3D> x3dModel::getNormalVectors()
{
	return this->normalVecs;
}

std::vector<Pair<float, float>> x3dModel::getTextureCoordinates()
{
	return this->uvcoords;
}

std::vector<int> x3dModel::getIndexListVec()
{
	return this->indexListVec;
}
