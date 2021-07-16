#include "x3dObject.h"
#include <vector>
#include <sstream>

x3dObject::x3dObject(int start, std::string infos, int id)
{
	this->specifier = id;
	this->startingLine = start;
}

x3dObject::x3dObject()
{
}

x3dObject::~x3dObject()
{
}

int x3dObject::getEndingLine()
{
	return this->endingLine;
}

int x3dObject::getStartingLine()
{
	return this->startingLine;
}

int x3dObject::getSpecifier()
{
	return this->specifier;
}

void x3dObject::setEndingLine(int end)
{
	this->endingLine = end;
}

void x3dObject::setTransformations(std::array<float, 16> mat)
{
	if (this->matrixSet == false) {
		this->matrix = mat;
		this->matrixSet = true;
	}
	else {
		this->matrix = Matrix::multiply(this->matrix, mat);
	}
}

std::array<float, 16> x3dObject::getMatrix()
{
	return this->matrix;
}

float x3dObject::extractFloat(std::string lookFor, std::string infos)
{
	infos.erase(std::remove(infos.begin(), infos.end(), ' '), infos.end());
	std::string tmp = infos.substr(infos.find(lookFor + "=\"") + lookFor.size()+2);
	tmp = tmp.substr(0, tmp.find("\"", 0));
	return std::stof(tmp);
}

int x3dObject::extractInt(std::string lookFor, std::string infos)
{
	infos.erase(std::remove(infos.begin(), infos.end(), ' '), infos.end());
	std::string tmp = infos.substr(infos.find(lookFor + "=\"") + lookFor.size() + 2);
	tmp = tmp.substr(0, tmp.find("\"", 0));
	return std::stoi(tmp);
}

std::string x3dObject::extractString(std::string lookFor, std::string infos)
{
	infos.erase(std::remove(infos.begin(), infos.end(), ' '), infos.end());
	std::string tmp = infos.substr(infos.find(lookFor + "=\"") + lookFor.size() + 2);
	tmp = tmp.substr(0, tmp.find("\"", 0));
	return tmp;
}

std::array<float, 3> x3dObject::extractFloatArray3(std::string lookFor, std::string infos)
{
	std::array<float, 3> temp;
	infos = infos.substr(infos.find(lookFor + "=\"") + lookFor.size() + 2);
	infos = infos.substr(0, infos.find("\"", 0));
	std::stringstream ss(infos);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);

	for (int i = 0; i < 3; i++){
		temp[i] = std::stof(vstrings[i]);
	}

	return temp;
}

std::array<float, 2> x3dObject::extractFloatArray2(std::string lookFor, std::string infos)
{
	std::array<float, 2> temp;
	infos = infos.substr(infos.find(lookFor + "=\"") + lookFor.size() + 2);
	infos = infos.substr(0, infos.find("\"", 0));
	std::stringstream ss(infos);
	std::istream_iterator<std::string> begin(ss);
	std::istream_iterator<std::string> end;
	std::vector<std::string> vstrings(begin, end);

	for (int i = 0; i < 2; i++) {
		temp[i] = std::stof(vstrings[i]);
	}

	return temp;
}

Vector3D x3dObject::extractVector3D(std::string lookFor, std::string infos)
{
	infos = infos.substr(infos.find(lookFor + "=\"") + lookFor.size() + 2);
	infos = infos.substr(0, infos.find("\"", 0));
	int count = 0;
	std::string word = "";
	Vector3D vec;
	for (int i = 0; i <= infos.size(); ++i) {
		if (infos[i] == ' ' || infos[i] == ',') {
			if (count == 0) {
				vec.x = std::stof(word);
				count++;
				word = "";
				continue;
			}
			if (count == 1) {
				vec.y = std::stof(word);
				count++;
				word = "";
				continue;
			}
		}
		else {
			word += infos[i];
		}
	}
	vec.z = std::stof(word);

	return vec;
}
