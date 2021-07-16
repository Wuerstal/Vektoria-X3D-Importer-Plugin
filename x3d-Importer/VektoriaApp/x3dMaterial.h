/*
Hält und wertet Informationen des im <Appearance> Tag definierten Materials.
Autor: Lukas Zickl
*/

#pragma once

#include <string>
#include "Vector3D.h"
#include "Pair.h"
#include <vector>

class x3dMaterial
{
public:
	x3dMaterial(std::string infos, std::vector<Pair<std::string, x3dMaterial*>> &materialDef);
	~x3dMaterial();


	Vector3D getDiffuseColor();
	Vector3D getEmissiveColor();
	Vector3D getSpecularColor();
	float getAmbientIntensity();
	float getShininess();
	float getTransparency();

private:
	void setDiffuceColor();
	void setEmissiveColor();
	void setSpecularColor();
	void setAmbientIntensity();
	void setShininess();
	void setParams();
	void setTransparency();

	Vector3D diffusecolor = Vector3D(0.8f, 0.8f, 0.8f, 0);
	Vector3D emissiveColor = Vector3D(0.f, 0.f, 0.f, 0.f);
	Vector3D specularColor = Vector3D(0.f, 0.f, 0.f, 0.f);
	float ambientIntensity = 0.2f;
	float shininess = 0.2f;
	float transparency = 0.0f;
	std::string info;
};

