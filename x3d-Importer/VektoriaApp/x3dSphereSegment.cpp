#include "x3dSphereSegment.h"

x3dSphereSegment::x3dSphereSegment(int start, std::string infos, int id)
{
	this->startingLine = start;
	this->specifier = id;
	setGeneral(infos);

	if (infos.find("radius") != std::string::npos) {
		this->radius = extractFloat("radius", infos);
	}

	if (infos.find("stepsize") != std::string::npos) {
		std::array<float, 2> t = extractFloatArray2("subdivision", infos);

		this->stepSize[0] = t[0];
		this->stepSize[1] = t[1];
	}

	if (infos.find("latitude") != std::string::npos) {
		std::string specificTransformation = infos;
		specificTransformation.erase(std::remove(specificTransformation.begin(), specificTransformation.end(), ' '), specificTransformation.end());
		specificTransformation = specificTransformation.substr(specificTransformation.find("latitude=\"") + 10);
		specificTransformation = specificTransformation.substr(0, specificTransformation.find("\"", 0));

		int count = 0;
		std::string word = "";
		for (int i = 0; i <= specificTransformation.size(); ++i) {
			if (specificTransformation[i] == ' ' || specificTransformation[i] == ',') {
				if (word == " ") {
					word = "";
					continue;
				}
				else {
					this->latitude.emplace_back(std::stof(word));
					word = "";
					continue;
				}
			}
			else {
				word += specificTransformation[i];
			}
		}
	}

	if (infos.find("longitude") != std::string::npos) {
		std::string specificTransformation = infos;
		specificTransformation.erase(std::remove(specificTransformation.begin(), specificTransformation.end(), ' '), specificTransformation.end());
		specificTransformation = specificTransformation.substr(specificTransformation.find("longitude=\"") + 11);
		specificTransformation = specificTransformation.substr(0, specificTransformation.find("\"", 0));

		int count = 0;
		std::string word = "";
		for (int i = 0; i <= specificTransformation.size(); ++i) {
			if (specificTransformation[i] == ' ' || specificTransformation[i] == ',') {
				if (word == " ") {
					word = "";
					continue;
				}
				else {
					this->longitude.emplace_back(std::stof(word));
					word = "";
					continue;
				}
			}
			else {
				word += specificTransformation[i];
			}
		}
	}
}

x3dSphereSegment::~x3dSphereSegment()
{
}

float x3dSphereSegment::getRadius()
{
	return this->radius;
}

float * x3dSphereSegment::getStepSize()
{
	return this->stepSize;
}

std::vector<float> x3dSphereSegment::getLatitude()
{
	return this->latitude;
}

std::vector<float> x3dSphereSegment::getLongitude()
{
	return this->longitude;
}
