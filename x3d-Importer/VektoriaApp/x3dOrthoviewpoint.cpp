#include "x3dOrthoviewpoint.h"
#include <algorithm>

x3dOrthoviewpoint::x3dOrthoviewpoint(int start, std::string info, int id)
{
	this->specifier = id;
	this->startingLine = start;
	generateGenerallParameters(info);

	if (info.find("fieldofview") != std::string::npos) {
		std::string fieldofview = info.substr(info.find("fieldofview=") + 13);
		fieldofview = fieldofview.substr(0, fieldofview.find("\"", 0));
		if (fieldofview.find("[") != std::string::npos) {

			fieldofview.erase(std::remove(fieldofview.begin(), fieldofview.end(), '['), fieldofview.end());
			fieldofview.erase(std::remove(fieldofview.begin(), fieldofview.end(), ']'), fieldofview.end());

			int count = 0;
			std::string word = "";
			for (int i = 0; i <= fieldofview.size(); ++i) {
				if (fieldofview[i] == ' ' || fieldofview[i] == ',') {
					if (count == 0) {
						this->orthoFov.x = std::stof(word);
						count++;
						word = "";
						continue;
					}
					if (count == 1) {
						this->orthoFov.y = std::stof(word);
						count++;
						word = "";
						continue;
					}
					if (count == 2) {
						this->orthoFov.z = std::stof(word);
						count++;
						word = "";
						continue;
					}
				}
				else {
					word += fieldofview[i];
				}
			}
			this->orthoFov.uv = std::stof(word);
		}
	}
}

x3dOrthoviewpoint::~x3dOrthoviewpoint()
{
}

Vector3D x3dOrthoviewpoint::getFov()
{
	return this->orthoFov;
}
