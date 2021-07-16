#pragma comment (lib, "urlmon.lib") 
#include "x3dTexture.h"
#include <algorithm>
#include <filesystem>
#include <iostream>
#include "Urlmon.h"
#include <fstream>

namespace fs = std::filesystem;

x3dTexture::x3dTexture(std::string info, std::vector<Pair<std::string, std::string>> &textureDef, bool downloadTex)
{
	if (info.find("<imagetexture") != std::string::npos) {
		this->texInfo = info.substr(info.find("<imagetexture") + 13);
		this->texInfo = this->texInfo.substr(0, this->texInfo.find("/>", 0));
		setUrl(textureDef, downloadTex);
		setRepeats();
	}
	else
		this->url = "";
}

x3dTexture::~x3dTexture()
{
}

void x3dTexture::setUrl(std::vector<Pair<std::string, std::string>>& textureDef, bool downloadTex)
{
	if (this->texInfo.find("url=") != std::string::npos) {
		this->url = this->texInfo.substr(this->texInfo.find("url=") + 5);
		while (this->url[0] == '\"') {
			this->url.erase(0, 1);
		}
		this->url = this->url.substr(0, this->url.find("\"", 0));

		if (downloadTex == true) {
			if (this->url.find("http") != std::string::npos) {
				downloadTexture();
			}
		}
	}
	if (this->texInfo.find("def=") != std::string::npos) {
		std::string temp = this->texInfo.substr(this->texInfo.find("def=") + 5);
		temp = temp.substr(0, temp.find("\"", 0));

		textureDef.emplace_back();
		textureDef.back().setA(temp);
		textureDef.back().setB(this->url);
	}
	if (this->texInfo.find("use=") != std::string::npos) {
		std::string temp = this->texInfo.substr(this->texInfo.find("use=") + 5);
		temp = temp.substr(0, temp.find("\"", 0));
		for (auto texture : textureDef) {
			if (temp == texture.getA()) {
				this->url = texture.getB();
			}
		}
	}
}

void x3dTexture::setRepeats()
{
	std::string tmp = this->texInfo;
	std::remove_if(tmp.begin(), tmp.end(), isspace);
	if (tmp.find("repeats=\"false\"") != std::string::npos)
			this->repeatU = false;
	if (tmp.find("repeatt=\"false\"") != std::string::npos)
		this->repeatV = false;
	if (tmp.find("scale=\"false\"") != std::string::npos)
		this->scale = false;
}

void x3dTexture::downloadTexture()
{
	char *inetAdress = new char[this->url.size() + 1];
	strcpy(inetAdress, this->url.c_str());
	std::size_t textureName = this->url.find_last_of("/");
	this->url = this->url.substr(textureName + 1);
	std::string localTmp = fs::temp_directory_path().string() + this->url;
	char *localAdress = new char[localTmp.size() + 1];
	strcpy(localAdress, localTmp.c_str());

	if (!std::filesystem::exists(localAdress))
	{
		HRESULT hr = URLDownloadToFile(NULL, inetAdress, localAdress, 0, NULL);
		std::ofstream file;
		file.open("log/x3d-pars.log", std::ios_base::app);
		if (hr != S_OK) {
			file << "X3D-Parsing-Error: Failed to download: " << inetAdress << "\n";
			this->url = "";
		}
		else {
			file << "File downloaded successfully: " << inetAdress << "\n";
			this->url = localAdress;
		}
		file.close();
	}
	else {
		this->url = localAdress;
	}
	
}

std::string x3dTexture::getUrl()
{
	return this->url;
}

