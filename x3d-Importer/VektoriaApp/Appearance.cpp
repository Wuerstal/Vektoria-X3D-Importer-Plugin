#include "Appearance.h"
#include "x3dObject.h"

Appearance::Appearance(int start, int end, std::string info, std::vector<Pair<std::string, std::string>> &textureDef, std::vector<Pair<std::string, x3dMaterial*>> &materialDef, bool downloadTexture)
{
	this->startingLine = start;
	this->endingLine = end;
	this->infos = info;
	this->material = new x3dMaterial(this->infos, materialDef);
	this->texture = new x3dTexture(this->infos, textureDef, downloadTexture);

	if (this->infos.find("alphaclipthreshold") != std::string::npos) {
		this->alphaClipThreshold = x3dObject::extractFloat("alphaclipthreshold", this->infos);
	}
	if (this->infos.find("<colormaskmode") != std::string::npos) {
		setColorMasking();
	}

	if (this->infos.find("<lineproperties") != std::string::npos) {
		setLineProperties();
	}

	if (this->infos.find("sortkey") != std::string::npos) {
		this->sortKey = x3dObject::extractInt("sortkey", this->infos);
	}

	if (this->infos.find("sorttype") != std::string::npos) {
		this->sortType = x3dObject::extractString("sorttype", this->infos);
	}
	this->infos = "";
}

Appearance::Appearance()
{
}

Appearance::~Appearance()
{
}

void Appearance::setColorMasking()
{
	this->colorMasking = true;
	std::string tmp = this->infos;
	std::remove_if(tmp.begin(), tmp.end(), isspace);
	if (tmp.find("maskr=\"false\"") != std::string::npos)
		this->maskR = false;
	if (tmp.find("maskg=\"false\"") != std::string::npos)
		this->maskG = false;
	if (tmp.find("maskb=\"false\"") != std::string::npos)
		this->maskB = false;
	if (tmp.find("maska=\"false\"") != std::string::npos)
		this->maskA = false;
	tmp = "";
}

void Appearance::setLineProperties()
{
	if (this->infos.find("applied=\"false\"") != std::string::npos)
		this->applied = false;
	if (this->infos.find("linetype") != std::string::npos) 
		this->lineType = x3dObject::extractInt("linetype", this->infos);
	if (this->infos.find("linewidthscalefactor") != std::string::npos)
		this->lineWidthScaleFactor = x3dObject::extractInt("linewidthscalefactor", this->infos);
}

int Appearance::getStartingLine()
{
	return this->startingLine;
}

int Appearance::getEndingLine()
{
	return this->endingLine;
}

bool Appearance::getMaskR()
{
	return this->maskR;
}

bool Appearance::getMaskG()
{
	return this->maskG;
}

bool Appearance::getMaskB()
{
	return this->maskB;
}

bool Appearance::getMaskA()
{
	return this->maskA;
}

x3dMaterial Appearance::getMaterial()
{
	return *this->material;
}

x3dTexture Appearance::getTexture()
{
	return *this->texture;
}
