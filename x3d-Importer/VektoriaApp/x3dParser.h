/*
Der Parser ließt die Datei Zeile für Zeile. Ruft bei erkennen eines Tags eine dazu passende Unterklasse von x3dObject auf. 
Die relevanten Informationen für diese werden dann in der Unterklasse ausgewertet und gespeichert.
getObjects gibt einen std::vector mit x3dObject Typen zurück, in dem sämtliche Geometrien, Beleuchtungselemente und Kameras gespeichert sind.
Autor: Lukas Zickl
*/

#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include "x3dObject.h"
#include "Appearance.h"
#include <stack>
#include "Matrix.h"

class x3dParser
{
public:
	x3dParser(std::ifstream &file, bool contentDownload, bool scene);
	~x3dParser();

	std::vector<x3dObject*> getObjects();

private:
	void parseComplete(std::ifstream & file);
	void parseGeosOnly(std::ifstream & file);
	void standardizeString(std::string & line);
	void prepare();
	void setTransformations();

	void parseXmlTag();
	void parseSubFile();
	void parseTransformation(std::ifstream &file);
	void parsePointLight(std::ifstream &file);
	void parseSpotLight(std::ifstream &file);
	void parseDirectionalLight(std::ifstream &file);
	void parseViewPoint(std::ifstream &file);
	void parseOrthoViewPoint(std::ifstream &file);
	void parseShape(std::ifstream &file, bool text);
	void parsePrimitives(std::ifstream &file, int startline);
	void parsePurePrimitives(std::ifstream &file);
	void parseIndexedTriangleSet(std::ifstream &file, int startline);
	void parseAppearance(std::ifstream &file, int startline);
	void parseText(std::ifstream &file, int startline);
	void parsePointSet(std::ifstream &file, int startline);


	std::vector<std::string> primitives{
		"<sphere>", "<box>", "<cone>", "<circle2d>", "<cylinder>", "<disk2d>", "<plane>", "<pyramid>", "<rectangle2d>", "<torus>", "<arc2d>", "<arcclose2d>", "<text>", "<dish>","<rectangulartorus>","<slopedcylinder>", "<snout>", "<spheresegment>"
	};
	std::vector<std::string> purePrimitives{
		"<sphere/>", "<box/>", "<cone/>", "<circle2d/>", "<cylinder/>", "<disk2d/>", "<plane/>", "<pyramid/>", "<rectangle2d/>", "<torus/>", "<arc2d/>", "<arcclose2d/>", "<text/>", "<dish/>","<rectangulartorus/>","<slopedcylinder/>", "<snout/>", "<spheresegment/>"
	};
	std::vector<Pair<std::string, std::string>> textureDef;
	std::vector<Pair<std::string, x3dMaterial*>> materialDef;

	std::vector<x3dObject*> Objects;
	std::vector<Matrix> Matricies;
	std::stack<Matrix> stack;

	std::string line;
	int lineCounter = 0;
	std::string xmlTag;
	Appearance* appearance;
	bool url = false;
	bool text = false;
	bool parseScene = false;
	std::string potentialUrl;
	std::string potentialText;
	bool hasAppearance = false;
	bool downloadContent = true;
};

