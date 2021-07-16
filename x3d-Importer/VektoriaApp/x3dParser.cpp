#pragma comment (lib, "urlmon.lib") 
#include "x3dParser.h"
#include "Urlmon.h"
#include <filesystem>

#include "x3dSubclasses.h"

namespace fs = std::filesystem;

x3dParser::x3dParser(std::ifstream &file, bool contentDownload, bool scene)
{
	prepare();
	this->parseScene = scene;
	this->downloadContent = contentDownload;
	if (scene == true) {
		parseComplete(file);
	}
	else {
		parseGeosOnly(file);
	}
	setTransformations();
}

x3dParser::~x3dParser()
{
}

std::vector<x3dObject*> x3dParser::getObjects()
{
	return this->Objects;
}

void x3dParser::parseComplete(std::ifstream & file)
{
	while (!file.eof())
	{
		std::getline(file, line);
		standardizeString(line);
		lineCounter++;

		if (line.find("<transform") != std::string::npos) {
			parseTransformation(file);
		}
		else if (line.find("</transform>") != std::string::npos) {
			stack.top().setEndingLine(lineCounter);
			Matricies.emplace_back(stack.top());
			stack.pop();
		}
		else if (line.find("<shape") != std::string::npos) {
			parseShape(file, true);
		}
		else if (line.find("<pointlight") != std::string::npos) {
			parsePointLight(file);
		}
		else if (line.find("<spotlight") != std::string::npos) {
			parseSpotLight(file);
		}
		else if (line.find("<directionallight") != std::string::npos) {
			parseDirectionalLight(file);
		}
		else if (line.find("<viewpoint") != std::string::npos) {
			parseViewPoint(file);
		}
		else if (line.find("<orthoviewpoint") != std::string::npos) {
			parseOrthoViewPoint(file);
		}
		else if (line.find("<inline") != std::string::npos) {
			parseSubFile();
		}
	}
	file.clear();
	file.seekg(0);
}

void x3dParser::parseGeosOnly(std::ifstream & file)
{
	while (!file.eof())
	{
		std::getline(file, line);
		standardizeString(line);
		lineCounter++;

		if (line.find("<transform") != std::string::npos) {
			parseTransformation(file);
		}
		else if (line.find("</transform>") != std::string::npos) {
			stack.top().setEndingLine(lineCounter);
			Matricies.emplace_back(stack.top());
			stack.pop();
		}
		else if (line.find("<shape") != std::string::npos) {
			parseShape(file, false);
		}
		else if (line.find("<inline") != std::string::npos) {
			parseSubFile();
		}
	}
	file.clear();
	file.seekg(0);
}

void x3dParser::standardizeString(std::string & line)
{
	if (line.find("url=") != std::string::npos) {
		potentialUrl = line.substr(line.find("url=") + 0);
		url = true;
	}
	if (line.find("string=") != std::string::npos) {
		potentialText = line.substr(line.find("string=") + 0);
		text = true;
		for (int i = 0; i < potentialText.size(); i++) {
			if (potentialText[i] == 39) {
				potentialText[i] = 34;
			}
		}
	}
	for (int i = 0; i < line.size(); i++) {
		if (line[i] >= 65 && line[i] <= 90) {
			line[i] += 32;
		}
		if (line[i] == 39) {
			line[i] = 34;
		}
		if (line[i] == 44) {
			line[i] = 32;
		}
	}
	if (url == true) {
		line = line.substr(0, line.find("url=", 0));
		line = line + potentialUrl;
		url = false;
	}
	if (text == true) {
		line = line.substr(0, line.find("string=", 0));
		line = line + potentialText;
		text = false;
	}
}

void x3dParser::prepare()
{
	Objects.clear();
	Objects.shrink_to_fit();
	Matricies.clear();
	Matricies.shrink_to_fit();
	lineCounter = 0;
}

void x3dParser::setTransformations()
{
	for (int i = 0; i < Objects.size(); i++) {
		int end = Objects[i]->getEndingLine();
		int start = Objects[i]->getStartingLine();
		for (int j = Matricies.size() - 1; j >= 0; j--) {
			if (end < Matricies[j].getEndingLine() && start > Matricies[j].getStartingLine()) {
				Objects[i]->setTransformations(Matricies[j].getMatrix());
			}
		}
	}
}

void x3dParser::parseXmlTag()
{
	xmlTag = line.substr(line.find("<"));
	xmlTag = xmlTag.substr(0, xmlTag.find(" ", 0));
	if (xmlTag.find(">") == std::string::npos) {
		xmlTag += ">";
	}
}

void x3dParser::parseSubFile()
{
	std::string newFilePath;
	newFilePath += x3dObject::extractString("url", line);

	if (this->downloadContent == true) {
		if (newFilePath.find("http") != std::string::npos) {
			char *inetAdress = new char[newFilePath.size() + 1];
			strcpy(inetAdress, newFilePath.c_str());
			std::size_t fileName = newFilePath.find_last_of("/");
			newFilePath = newFilePath.substr(fileName + 1);
			std::string localTmp = fs::temp_directory_path().string() + newFilePath;
			char *localAdress = new char[localTmp.size() + 1];
			strcpy(localAdress, localTmp.c_str());
			
			HRESULT hr = URLDownloadToFile(NULL, inetAdress, localAdress, 0, NULL);
			std::ofstream file;
			file.open("log/x3d-pars.log", std::ios_base::app);
			if (hr != S_OK) {
				file << "X3D-Parsing-Error: Failed to download: " << inetAdress << "\n";
				newFilePath = "";
			}
			else {
				file << "File downloaded successfully: " << inetAdress << "\n";
				newFilePath = localAdress;
			}
			file.close();
		}
	}

	if (parseScene == true) {
		std::ifstream newfile;
		newfile.open(newFilePath);

		if (newfile.is_open()) {
			parseComplete(newfile);
			newfile.close();
		}
	}
	else {
		std::ifstream newfile;
		newfile.open(newFilePath);

		if (newfile.is_open()) {
			parseGeosOnly(newfile);
			newfile.close();
		}
	}
}

void x3dParser::parseTransformation(std::ifstream &file)
{
	std::string allTransformations = line;
	while (line.find(">") == std::string::npos) {
		std::getline(file, line);
		standardizeString(line);
		lineCounter++;
		allTransformations += line;
	}
	Matrix* mat = new Matrix(allTransformations);
	mat->setStartingLine(lineCounter);
	stack.push(*mat);
}

void x3dParser::parsePointLight(std::ifstream & file)
{
	std::string lightInfo = line;
	int pointStartLine = lineCounter;
	while (line.find("/>") == std::string::npos) {
		std::getline(file, line);
		standardizeString(line);
		lineCounter++;
		lightInfo += line;
	}
	x3dObject* pl = new x3dPointLight(pointStartLine, lightInfo, 200);
	pl->setEndingLine(lineCounter);
	Objects.push_back(pl);
}

void x3dParser::parseSpotLight(std::ifstream & file)
{
	std::string lightInfo = line;
	int spotStartLine = lineCounter;
	while (line.find("/>") == std::string::npos) {
		std::getline(file, line);
		standardizeString(line);
		lineCounter++;
		lightInfo += line;
	}
	x3dObject* sl = new x3dSpotLight(spotStartLine, lightInfo, 201);
	sl->setEndingLine(lineCounter);
	Objects.push_back(sl);
}

void x3dParser::parseDirectionalLight(std::ifstream & file)
{
	std::string lightInfo = line;
	int directionalStartLine = lineCounter;
	while (line.find("/>") == std::string::npos) {
		std::getline(file, line);
		standardizeString(line);
		lineCounter++;
		lightInfo += line;
	}
	x3dObject* dl = new x3dDirectionalLight(directionalStartLine, lightInfo, 202);
	dl->setEndingLine(lineCounter);
	Objects.push_back(dl);
}

void x3dParser::parseViewPoint(std::ifstream & file)
{
	std::string camInfo = line;
	int viewStartLine = lineCounter;
	while (line.find("/>") == std::string::npos) {
		std::getline(file, line);
		standardizeString(line);
		lineCounter++;
		camInfo += line;
	}
	x3dObject* vp = new x3dViewpoint(viewStartLine, camInfo, 300);
	vp->setEndingLine(lineCounter);
	Objects.push_back(vp);
}

void x3dParser::parseOrthoViewPoint(std::ifstream & file)
{
	std::string camInfo = line;
	int viewStartLine = lineCounter;
	while (line.find("/>") == std::string::npos) {
		std::getline(file, line);
		standardizeString(line);
		lineCounter++;
		camInfo += line;
	}
	x3dObject* ovp = new x3dOrthoviewpoint(viewStartLine, camInfo, 301);
	ovp->setEndingLine(lineCounter);
	Objects.push_back(ovp);
}

void x3dParser::parseShape(std::ifstream & file, bool text)
{
	int startline = lineCounter;
	hasAppearance = false;
	while (line.find("</shape") == std::string::npos) {
		std::getline(file, line);
		standardizeString(line);
		lineCounter++;
		if (line.find("<") != std::string::npos) {
			parseXmlTag();
		}
		if (std::find(primitives.begin(), primitives.end(), xmlTag) != primitives.end()) {
			parsePrimitives(file, startline);
		}
		else if (std::find(purePrimitives.begin(), purePrimitives.end(), xmlTag) != purePrimitives.end()) {
			parsePurePrimitives(file);
		}
		else if (line.find("<indexedtriangleset") != std::string::npos) {
			parseIndexedTriangleSet(file, startline);
		}
		else if (line.find("<pointset") != std::string::npos) {
			parsePointSet(file, startline);
		}
		else if (line.find("<appearance") != std::string::npos) {
			parseAppearance(file, startline);
		}
		if (text == true) {
			if (line.find("<text") != std::string::npos) {
				parseText(file, startline);
			}
		}
	}
	if (hasAppearance == true) {
		dynamic_cast<x3dShape*>(Objects.back())->setAppearance(*appearance);
	}
}

void x3dParser::parsePrimitives(std::ifstream &file, int startline)
{
	std::string shapeInfo = line;
	if (xmlTag == "<box>") {
		while (line.find("</box") == std::string::npos) {
			std::getline(file, line);
			standardizeString(line);
			lineCounter++;
			shapeInfo += line;
		}
		x3dObject* box = new x3dBox(startline, shapeInfo, 100);
		box->setEndingLine(lineCounter);
		Objects.push_back(box);
	}
	else if (xmlTag == "<sphere>") {
		while (line.find("</sphere") == std::string::npos) {
			std::getline(file, line);
			standardizeString(line);
			lineCounter++;
			shapeInfo += line;
		}
		x3dObject* sphere = new x3dSphere(startline, shapeInfo, 101);
		sphere->setEndingLine(lineCounter);
		Objects.push_back(sphere);
	}
	else if (xmlTag == "<cone>") {
		while (line.find("</cone") == std::string::npos) {
			std::getline(file, line);
			standardizeString(line);
			lineCounter++;
			shapeInfo += line;
		}
		x3dObject* cone = new x3dCone(startline, shapeInfo, 102);
		cone->setEndingLine(lineCounter);
		Objects.push_back(cone);
	}
	else if (xmlTag == "<circle2d>") {
		while (line.find("</circle2d") == std::string::npos) {
			std::getline(file, line);
			standardizeString(line);
			lineCounter++;
			shapeInfo += line;
		}
		x3dObject* circle2d = new x3dCircle2D(startline, shapeInfo, 103);
		circle2d->setEndingLine(lineCounter);
		Objects.push_back(circle2d);
	}
	else if (xmlTag == "<arc2d>") {
		while (line.find("</arc2d") == std::string::npos) {
			std::getline(file, line);
			standardizeString(line);
			lineCounter++;
			shapeInfo += line;
		}
		x3dObject* arc2d = new x3dArc2D(startline, shapeInfo, 104);
		arc2d->setEndingLine(lineCounter);
		Objects.push_back(arc2d);
	}
	else if (xmlTag == "<arcclose2d>") {
		while (line.find("</arcclose2d") == std::string::npos) {
			std::getline(file, line);
			standardizeString(line);
			lineCounter++;
			shapeInfo += line;
		}
		x3dObject* arcclose2d = new x3dArcClose2D(startline, shapeInfo, 105);
		arcclose2d->setEndingLine(lineCounter);
		Objects.push_back(arcclose2d);
	}
	else if (xmlTag == "<cylinder>") {
		while (line.find("</cylinder") == std::string::npos) {
			std::getline(file, line);
			standardizeString(line);
			lineCounter++;
			shapeInfo += line;
		}
		x3dObject* cylinder = new x3dCylinder(startline, shapeInfo, 106);
		cylinder->setEndingLine(lineCounter);
		Objects.push_back(cylinder);
	}
	else if (xmlTag == "<disk2d>") {
		while (line.find("</disk2d") == std::string::npos) {
			std::getline(file, line);
			standardizeString(line);
			lineCounter++;
			shapeInfo += line;
		}
		x3dObject* disk2d = new x3dDisk2D(startline, shapeInfo, 107);
		disk2d->setEndingLine(lineCounter);
		Objects.push_back(disk2d);
	}
	else if (xmlTag == "<plane>") {
		while (line.find("</plane") == std::string::npos) {
			std::getline(file, line);
			standardizeString(line);
			lineCounter++;
			shapeInfo += line;
		}
		x3dObject* plane = new x3dPlane(startline, shapeInfo, 108);
		plane->setEndingLine(lineCounter);
		Objects.push_back(plane);
	}
	else if (xmlTag == "<rectangle2d>") {
		while (line.find("</plane") == std::string::npos) {
			std::getline(file, line);
			standardizeString(line);
			lineCounter++;
			shapeInfo += line;
		}
		x3dObject* plane = new x3dPlane(startline, shapeInfo, 108);
		plane->setEndingLine(lineCounter);
		Objects.push_back(plane);
	}
	else if (xmlTag == "<pyramid>") {
		while (line.find("</pyramid") == std::string::npos) {
			std::getline(file, line);
			standardizeString(line);
			lineCounter++;
			shapeInfo += line;
		}
		x3dObject* pyramid = new x3dPyramid(startline, shapeInfo, 109);
		pyramid->setEndingLine(lineCounter);
		Objects.push_back(pyramid);
	}
	else if (xmlTag == "<torus>") {
		while (line.find("</torus") == std::string::npos) {
			std::getline(file, line);
			standardizeString(line);
			lineCounter++;
			shapeInfo += line;
		}
		x3dObject* torus = new x3dTorus(startline, shapeInfo, 110);
		torus->setEndingLine(lineCounter);
		Objects.push_back(torus);
	}
	else if (xmlTag == "<dish>") {
		while (line.find("</dish") == std::string::npos) {
			std::getline(file, line);
			standardizeString(line);
			lineCounter++;
			shapeInfo += line;
		}
		x3dObject* dish = new x3dDish(startline, shapeInfo, 111);
		dish->setEndingLine(lineCounter);
		Objects.push_back(dish);
	}
	else if (xmlTag == "<rectangulartorus>") {
		while (line.find("</rectangulartorus") == std::string::npos) {
			std::getline(file, line);
			standardizeString(line);
			lineCounter++;
			shapeInfo += line;
		}
		x3dObject* rectorus = new x3dRectangularTorus(startline, shapeInfo, 112);
		rectorus->setEndingLine(lineCounter);
		Objects.push_back(rectorus);
	}
	else if (xmlTag == "<slopedcylinder>") {
		while (line.find("</slopedcylinder") == std::string::npos) {
			std::getline(file, line);
			standardizeString(line);
			lineCounter++;
			shapeInfo += line;
		}
		x3dObject* slopedCyl = new x3dSlopedCylinder(startline, shapeInfo, 113);
		slopedCyl->setEndingLine(lineCounter);
		Objects.push_back(slopedCyl);
	}
	else if (xmlTag == "<snout>") {
		while (line.find("</snout") == std::string::npos) {
			std::getline(file, line);
			standardizeString(line);
			lineCounter++;
			shapeInfo += line;
		}
		x3dObject* snout = new x3dSnout(startline, shapeInfo, 114);
		snout->setEndingLine(lineCounter);
		Objects.push_back(snout);
	}
	else if (xmlTag == "<spheresegment>") {
		while (line.find("</spheresegment") == std::string::npos) {
			std::getline(file, line);
			standardizeString(line);
			lineCounter++;
			shapeInfo += line;
		}
		x3dObject* ssg = new x3dSphereSegment(startline, shapeInfo, 115);
		ssg->setEndingLine(lineCounter);
		Objects.push_back(ssg);
	}
}

void x3dParser::parsePurePrimitives(std::ifstream & file)
{
	std::string shapeInfo = line;
	if (xmlTag == "<box/>") {
		x3dObject* box = new x3dBox(lineCounter, shapeInfo, 100);
		box->setEndingLine(lineCounter);
		Objects.push_back(box);
	}
	else if (xmlTag == "<sphere/>") {
		x3dObject* sphere = new x3dSphere(lineCounter, shapeInfo, 101);
		sphere->setEndingLine(lineCounter);
		Objects.push_back(sphere);
	}
	else if (xmlTag == "<cone/>") {
		x3dObject* cone = new x3dCone(lineCounter, shapeInfo, 102);
		cone->setEndingLine(lineCounter);
		Objects.push_back(cone);
	}
	else if (xmlTag == "<circle2d/>") {
		x3dObject* circle2d = new x3dCircle2D(lineCounter, shapeInfo, 103);
		circle2d->setEndingLine(lineCounter);
		Objects.push_back(circle2d);
	}
	else if (xmlTag == "<arc2d/>") {
		x3dObject* arc2d = new x3dArc2D(lineCounter, shapeInfo, 104);
		arc2d->setEndingLine(lineCounter);
		Objects.push_back(arc2d);
	}
	else if (xmlTag == "<arcclose2d/>") {
		x3dObject* arcclose2d = new x3dArcClose2D(lineCounter, shapeInfo, 105);
		arcclose2d->setEndingLine(lineCounter);
		Objects.push_back(arcclose2d);
	}
	else if (xmlTag == "<cylinder/>") {
		x3dObject* cylinder = new x3dCylinder(lineCounter, shapeInfo, 106);
		cylinder->setEndingLine(lineCounter);
		Objects.push_back(cylinder);
	}
	else if (xmlTag == "<disk2d/>") {
		x3dObject* disk2d = new x3dDisk2D(lineCounter, shapeInfo, 107);
		disk2d->setEndingLine(lineCounter);
		Objects.push_back(disk2d);
	}
	else if (xmlTag == "<plane/>") {
		x3dObject* plane = new x3dPlane(lineCounter, shapeInfo, 108);
		plane->setEndingLine(lineCounter);
		Objects.push_back(plane);
	}
	else if (xmlTag == "<rectangle2d/>") {
		x3dObject* plane = new x3dPlane(lineCounter, shapeInfo, 108);
		plane->setEndingLine(lineCounter);
		Objects.push_back(plane);
	}
	else if (xmlTag == "<pyramid/>") {
		x3dObject* pyramid = new x3dPyramid(lineCounter, shapeInfo, 109);
		pyramid->setEndingLine(lineCounter);
		Objects.push_back(pyramid);
	}
	else if (xmlTag == "<torus/>") {
		x3dObject* torus = new x3dTorus(lineCounter, shapeInfo, 110);
		torus->setEndingLine(lineCounter);
		Objects.push_back(torus);
	}
	else if (xmlTag == "<dish/>") {
		x3dObject* dish = new x3dDish(lineCounter, shapeInfo, 111);
		dish->setEndingLine(lineCounter);
		Objects.push_back(dish);
	}
	else if (xmlTag == "<rectangulartorus/>") {
		x3dObject* rectorus = new x3dRectangularTorus(lineCounter, shapeInfo, 112);
		rectorus->setEndingLine(lineCounter);
		Objects.push_back(rectorus);
	}
	else if (xmlTag == "<slopedcylinder/>") {
		x3dObject* slopedCyl = new x3dSlopedCylinder(lineCounter, shapeInfo, 113);
		slopedCyl->setEndingLine(lineCounter);
		Objects.push_back(slopedCyl);
	}
	else if (xmlTag == "<snout/>") {
		x3dObject* snout = new x3dSnout(lineCounter, shapeInfo, 114);
		snout->setEndingLine(lineCounter);
		Objects.push_back(snout);
	}
	else if (xmlTag == "<spheresegment/>") {
		x3dObject* ssg = new x3dSphereSegment(lineCounter, shapeInfo, 115);
		ssg->setEndingLine(lineCounter);
		Objects.push_back(ssg);
	}
}

void x3dParser::parseIndexedTriangleSet(std::ifstream &file, int startline)
{
	std::string geoInfo = line;
	while (line.find("</indexedtriangleset") == std::string::npos) {
		std::getline(file, line);
		standardizeString(line);
		lineCounter++;
		geoInfo += line;
	}
	x3dObject* model = new x3dModel(startline, geoInfo, 0);
	model->setEndingLine(lineCounter);
	Objects.push_back(std::move(model));
}

void x3dParser::parsePointSet(std::ifstream & file, int startline)
{
	std::string geoInfo = line;
	while (line.find("</pointset") == std::string::npos) {
		std::getline(file, line);
		standardizeString(line);
		lineCounter++;
		geoInfo += line;
	}
	x3dObject* ps = new x3dPointSet(startline, geoInfo, 1);
	ps->setEndingLine(lineCounter);
	Objects.push_back(std::move(ps));
}

void x3dParser::parseAppearance(std::ifstream & file, int startline)
{
	int startAppearance = lineCounter;
	std::string appearInfo = line;
	while (line.find("</appearance") == std::string::npos) {
		std::getline(file, line);
		standardizeString(line);
		lineCounter++;
		appearInfo += line;
	}
	appearance = new Appearance(startAppearance, lineCounter, appearInfo, textureDef, materialDef, downloadContent);
	hasAppearance = true;
}

void x3dParser::parseText(std::ifstream & file, int startline)
{
	std::string textInfo = line;
	while (line.find("</text") == std::string::npos) {
		std::getline(file, line);
		standardizeString(line);
		lineCounter++;
		textInfo += line;
	}
	x3dObject* text = new x3dText(startline, textInfo, 400);
	text->setEndingLine(lineCounter);
	Objects.push_back(text);
}