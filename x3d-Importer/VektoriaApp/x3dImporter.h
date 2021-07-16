/*
Schnittstellen-Klasse zwischen dem x3dParser und der VektoriaEngine. 
Der x3dImporter nutzt die Informationen, die der Parser liefert, um daraus Vektoria Objekte zu erzeugen.
*/

#pragma once
#include "Vektoria\Root.h"
#include <stack>
#include "x3dShape.h"
#include "Vector3D.h"
#include "Pair.h"
#include "Matrix.h"
#include "x3dObject.h"
#include "x3dParser.h"

using namespace Vektoria;

class x3dImporter
{
public:
	///<summary> Importer für .x3d Dateien.</summary>
	x3dImporter();
	~x3dImporter();

	///<summary> Importiert die vorhandenen Geometrien einer .x3d-Datei. Enthält die Szene Text, so muss die gesamte Scene importiert werden (siehe .importScene())</summary>
	///<param name="filePath">Pfad zur Datei</param>
	///<param name="geometry">CGeo Objekt, in welcher die importierte Geometrie gespeichert wird</param>
	///<param name="downloadContent">Falls true, werden Texturen und Modelle, die als Internet-Url angegeben sind, in den temporären Windowsordner heruntergeladen und angewandt. Falls false, nicht.</param>
	void importShape(std::string filePath, CGeo &geometry, bool downloadContent = true);

	///<summary> Importiert die gesamte Szene einer .x3d-Datei mit Text-Elementen, Beleuchtung und Kameras. </summary>
	///<param name="filePath">Pfad zur Datei</param>
	///<param name="geometry">CGeo Objekt, in welcher die importierte Geometrie gespeichert wird</param>
	///<param name="scene">CScene Objekt, in welche die Lichtquellen importiert werden sollen</param>
	///<param name="cameraPlacements">CPlacements Objekt, in welcher die importierten Kameras gespeichert werden sollen</param>
	///<param name="downloadContent">Falls true, werden Texturen und Modelle, die als Internet-Url angegeben sind, in den temporären Windowsordner heruntergeladen und angewandt. Falls false, nicht.</param>
	void importScene(std::string filePath, CGeo &geometry, CScene& scene, CPlacements& cameraPlacements, bool downloadContent = true);

private:
	//Ruft den Parser auf
	void readFile(std::ifstream &file);

	void createParentShapes(CGeo &geometry, int i);
	void addChildShapes(CGeo &geometry, int i);
	void createModel(CGeo &geometry, bool child, int iterator);
	void createPointList(CGeo &geometry, bool child, int iterator);
	void createText(CScene &scene, int i);
	void applyTransformations(CGeo &geo, int i);
	void applyTransformationsPlacement(CPlacement &placement, int i);
	void applyColor(CGeo &geometry, x3dShape shape);
	void createLights(CScene& scene, int iterator);
	void createViewPoints(CPlacements& cameraPlacements, int iterator);

	//Schnittstellen-Funktionen
	CHVector vectorToCHVector(Vector3D vec);
	CColor vectorToCColor(Vector3D vec);

	//Containers
	std::vector<x3dObject*> Objects;
	std::vector<CVertex> vertecies;

	//Variables
	bool texDown;
	bool importFullScene = false;
	bool isParent = true;

	x3dParser *parser;
};

