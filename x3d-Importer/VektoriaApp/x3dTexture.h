#pragma once
#include <string>
#include <vector>
#include "Pair.h"

class x3dTexture
{
public:
	x3dTexture(std::string info, std::vector<Pair<std::string, std::string>> &textureDef, bool downloadTexture);
	~x3dTexture();


	std::string getUrl();

private:
	void setUrl(std::vector<Pair<std::string, std::string>> &textureDef, bool downloadTex);
	void setRepeats();
	void downloadTexture();


	std::string url;
	bool repeatU = true;
	bool repeatV = true;
	bool scale = true;
	std::string texInfo;
	//A=def, B=url
	
};

