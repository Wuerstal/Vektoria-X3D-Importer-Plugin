#include "x3dImporter.h"

#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>

#include "x3dParser.h"
#include "CGeoCircle2D.h"
#include "CGeoPyramid.h"
#include "CGeoArcClose2D.h"
#include "Matrix.h"

#include "x3dSubclasses.h"



x3dImporter::x3dImporter() {

}

x3dImporter::~x3dImporter() {
	
}

void x3dImporter::importShape(std::string filePath, CGeo &geometry, bool downloadTextures)
{
	texDown = downloadTextures;
	std::ifstream file;
	file.open(filePath);

	if (file.is_open()) {
		readFile(file);
	}
	else {
		char * cstr = new char[filePath.length() + 1];
		ULError("Datei \"%s\" nicht gefunden", std::strcpy(cstr, filePath.c_str()));
		file.close();
		return;
	}


	file.close();

	if (importFullScene == false) {
		for (int i = 0; i < Objects.size(); i++) {
			int spec = Objects[i]->getSpecifier();
			if (i == 0) {
				if (spec == 0) {
					createModel(geometry, false, i);
				}
				else {
					createParentShapes(geometry, i);
				}
			}
			else {
				if (spec == 0) {
					createModel(geometry, true, i);
				}
				else {
					addChildShapes(geometry, i);
				}
			}
		}

		Objects.clear();
		Objects.shrink_to_fit();
	}
}


void x3dImporter::importScene(std::string filePath, CGeo & geometry, CScene& scene, CPlacements& cameraPlacements, bool downloadTextures)
{
	importFullScene = true;
	importShape(filePath, geometry, downloadTextures);

	for (int i = 0; i < Objects.size(); i++) {
		int spec = Objects[i]->getSpecifier();
		if (spec == 0) {
			if (isParent == true) {
				createModel(geometry, false, i);
				isParent = false;
			}
			else
				createModel(geometry, true, i);
		}
		else if (spec == 1) {
			if (isParent == true) {
				createPointList(geometry, false, i);
				isParent = false;
			}
			else
				createPointList(geometry, true, i);
		}
		else if (spec >= 100 && spec < 200) {
			if (isParent == true) {
				createParentShapes(geometry, i);
				isParent = false;
			}
			else
				addChildShapes(geometry, i);
		}
		else if (spec >= 200 && spec < 300)
			createLights(scene, i);
		else if (spec >= 300 && spec < 400)
			createViewPoints(cameraPlacements, i);
		else if (spec == 400) {
			createText(scene, i);
		}
	}
	
	Objects.clear();
	Objects.shrink_to_fit();
	importFullScene = false;
	isParent = true;
}

void x3dImporter::readFile(std::ifstream &file)
{
	x3dParser parser(file, texDown, importFullScene);
	Objects = parser.getObjects();
}

void x3dImporter::createLights(CScene& scene, int iterator)
{
	CPlacement* lightPlace = new CPlacement();
	int spec = Objects[iterator]->getSpecifier();
	switch (spec) {
		case 200: {
			x3dPointLight* pl = dynamic_cast<x3dPointLight*>(Objects[iterator]);
			CLightRadial* pointlight = new CLightRadial();
			pointlight->Init(vectorToCColor(pl->getColor()), pl->getIntensity());
			pointlight->SetRadius(pl->getRadius());
			int sms = pl->getShadowMapSize();
			pointlight->SetShadowMapResolution(sms, sms);
			if (pl->getOn() == false) {
				pointlight->SwitchOff();
			}
			lightPlace->AddLightRadial(pointlight);
			scene.AddPlacement(lightPlace);
			applyTransformationsPlacement(*lightPlace, iterator);
			lightPlace->TranslateDelta(vectorToCHVector(pl->getLocation()));
			break;
		}
		case 201: {
			x3dSpotLight* sl = dynamic_cast<x3dSpotLight*>(Objects[iterator]);
			CLightSpot* spotlight = new CLightSpot();
			spotlight->Init(vectorToCColor(sl->getColor()), sl->getInnerAngle(), sl->getOuterAngle());
			spotlight->SetMaxDistance(sl->getMaxDist());
			spotlight->SetRadius(sl->getMaxDist());
			int sms = sl->getShadowMapSize();
			spotlight->SetShadowMapResolution(sms, sms);
			if (sl->getOn() == false) {
				spotlight->SwitchOff();
			}
			lightPlace->AddLightSpot(spotlight);
			scene.AddPlacement(lightPlace);
			applyTransformationsPlacement(*lightPlace, iterator);
			lightPlace->TranslateDelta(vectorToCHVector(sl->getLocation()));
			break;
		}
		case 202: {
			x3dDirectionalLight* dl = dynamic_cast<x3dDirectionalLight*>(Objects[iterator]);
			CLightParallel* parrallelLight = new CLightParallel();
			parrallelLight->Init(vectorToCHVector(dl->getDirection()), vectorToCColor(dl->getColor()));
			int sms = dl->getShadowMapSize();
			parrallelLight->SetShadowMapResolution(sms, sms);
			if (dl->getOn() == false) {
				parrallelLight->SwitchOff();
			}
			scene.AddLightParallel(parrallelLight);
			return;
		}
	}
}

void x3dImporter::createViewPoints(CPlacements& cameraPlacements, int iterator)
{
	CPlacement* camplace = new CPlacement;
	CCamera* camera = new CCamera;
	int spec = Objects[iterator]->getSpecifier();
	switch (spec) {
		case 300: {
			x3dViewpoint* vp = dynamic_cast<x3dViewpoint*>(Objects[iterator]);
			camera->Init(vp->getFov(), vp->getNear(), vp->getFar());
			camplace->AddCamera(camera);
			applyTransformationsPlacement(*camplace, iterator);
			camplace->TranslateDelta(vectorToCHVector(vp->getPosition()));
			cameraPlacements.Add(camplace);
			break;
		}
		case 301: {
			x3dOrthoviewpoint* ovp = dynamic_cast<x3dOrthoviewpoint*>(Objects[iterator]);
			camera->Init(QUARTERPI, ovp->getNear(), ovp->getFar());
			camplace->AddCamera(camera);
			applyTransformationsPlacement(*camplace, iterator);
			camplace->TranslateDelta(vectorToCHVector(ovp->getPosition()));
			cameraPlacements.Add(camplace);
			break;
		}
	}
}

void x3dImporter::applyColor(CGeo &geometry, x3dShape shape)
{

	if (shape.getHasAppearance() == true) {
		CMaterial* matDiff = new CMaterial;
		Appearance app = shape.getAppearance();
		x3dMaterial mat = app.getMaterial();
		x3dTexture tex = app.getTexture();
		if (!app.getTexture().getUrl().empty()) {
			char *cstr = new char[tex.getUrl().size() + 1];
			strcpy(cstr, tex.getUrl().c_str());
			matDiff->MakeTextureDiffuse(cstr);
			matDiff->SetTextureSpecularBlack();
			geometry.SetMaterial(matDiff);
			return;
		}
		else {
			//Materialsysteme sind verhältnismäßig inkompatibel. Möglichkeiten die Farbe des Speculars, Emission zu setzen. + Specular oft in Vektoria viel stärker.
			matDiff->MakeTextureDiffuse("textures/black_image.jpg");
			matDiff->Translate(vectorToCColor(mat.getDiffuseColor()));
			matDiff->SetSpecularSharpness(mat.getShininess());
			matDiff->SetTransparency(mat.getTransparency());
			matDiff->SetSpecularStrength(mat.getShininess());
			matDiff->SetTextureSpecularBlack();
			geometry.SetMaterial(matDiff);
			return;
		}
	}
}

CHVector x3dImporter::vectorToCHVector(Vector3D vec)
{
	CHVector* newVec = new CHVector;
	newVec->x = vec.x;
	newVec->y = vec.y;
	newVec->z = vec.z;
	newVec->w = vec.uv;
	return *newVec;
}

CColor x3dImporter::vectorToCColor(Vector3D vec)
{
	CColor* newColor = new CColor;
	newColor->m_frR = vec.x;
	newColor->m_frG = vec.y;
	newColor->m_frB = vec.z;

	return *newColor;
}

void x3dImporter::createParentShapes(CGeo &geometry, int i)
{
	int spec = Objects[i]->getSpecifier();
	switch (spec) {
		case 100: {
			x3dBox* box = dynamic_cast<x3dBox*>(Objects[i]);
			CGeoCube* geo = new CGeoCube;
			geo->Init(box->getBoxSize()[0], box->getBoxSize()[1], box->getBoxSize()[2], NULL);
			applyTransformations(*geo, 0);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.CopyHierarchy(*geo);
			delete geo;
			break; 
		}
		case 101: {
			x3dSphere* sphere = dynamic_cast<x3dSphere*>(Objects[i]);
			CGeoSphere* geo = new CGeoSphere;
			geo->Init(sphere->getSphereRadius(), NULL);
			applyTransformations(*geo, 0);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.CopyHierarchy(*geo->CopyToTriangleList());
			delete geo;
			break;
		}
		case 102: {
			x3dCone* cone = dynamic_cast<x3dCone*>(Objects[i]);
			CGeoCylinder* geo = new CGeoCylinder;
			geo->Init(cone->getConeBottomRadius(), cone->getConeTopRadius(), cone->getConeHeight(), NULL);
			geo->Transform(CHMat(1, 0, 0, 0, 0, 1, 0, -cone->getConeHeight() / 2, 0, 0, 1, 0, 0, 0, 0, 1));
			applyTransformations(*geo, 0);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.CopyHierarchy(*geo->CopyToTriangleList());
			delete geo;
			break;
		}
		case 103: {
			x3dCircle2D* circle = dynamic_cast<x3dCircle2D*>(Objects[i]);
			CGeoCircle2D* geo = new CGeoCircle2D(circle->getCircleRadius(), 360, 0);
			applyTransformations(*geo, 0);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.CopyHierarchy(*geo);
			delete geo;
			break;
		}
		case 104: {
			x3dArc2D* arc = dynamic_cast<x3dArc2D*>(Objects[i]);
			CGeoCircle2D* geo = new CGeoCircle2D(arc->getArcRadius(), arc->getDegree(), arc->getStartAngleInDegree());
			applyTransformations(*geo, 0);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.CopyHierarchy(*geo);
			delete geo;
			break;
		}
		case 105: {
			x3dArcClose2D* arcclose = dynamic_cast<x3dArcClose2D*>(Objects[i]);
			CGeoArcClose2D* geo = new CGeoArcClose2D(arcclose->getArcClosedRadius(), arcclose->getDegree(), arcclose->getStartAngleInDegree());
			applyTransformations(*geo, i);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.CopyHierarchy(*geo->CopyToTriangleList());
			delete geo;
			break;
		}
		case 106: {
			x3dCylinder* cylinder = dynamic_cast<x3dCylinder*>(Objects[i]);
			CGeoCylinder* geo = new CGeoCylinder;
			geo->Init(cylinder->getCylinderRadius(), cylinder->getCylinderRadius(), cylinder->getCylinderHeight(), NULL);
			geo->Transform(CHMat(1, 0, 0, 0, 0, 1, 0, -cylinder->getCylinderHeight() / 2, 0, 0, 1, 0, 0, 0, 0, 1));
			applyTransformations(*geo, 0);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.CopyHierarchy(*geo->CopyToTriangleList());
			delete geo;
			break;
		}
		case 107: {
			x3dDisk2D* disk2d = dynamic_cast<x3dDisk2D*>(Objects[i]);
			CGeoTube* geo = new CGeoTube;
			geo->InitStraight(disk2d->getDiskInnerRadius(), disk2d->getDiskOuterRadius(), 0.01f, NULL);
			geo->Transform(CHMat(1.f, 0.f, 0.f, 0.f, 0.f, float(cos(1.5708)), float(-sin(1.5708)), 0.f, 0.f, float(sin(1.5708)), float(cos(1.5708)), 0.f, 0.f, 0.f, 0.f, 1.f));
			applyTransformations(*geo, 0);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.CopyHierarchy(*geo->CopyToTriangleList());
			delete geo;
			break;
		}
		case 108: {
			x3dPlane* plane = dynamic_cast<x3dPlane*>(Objects[i]);
			CGeoQuad* geo = new CGeoQuad;
			geo->Init(plane->getPlaneSize()[0], plane->getPlaneSize()[1], NULL);
			
			//geo->Transform(CHMat(1, 0, 0, plane->planecenter[0], 0, 1, 0, plane->planecenter[1], 0, 0, 1, plane->planecenter[2], 0, 0, 0, 1));
			
			applyTransformations(*geo, 0);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.CopyHierarchy(*geo->CopyToTriangleList());
			delete geo;
			break;
		}
		case 109: {
			x3dPyramid* pyr = dynamic_cast<x3dPyramid*>(Objects[i]);
			CGeoPyramid* geo = new CGeoPyramid;
			geo->Initialize(pyr->getHeight(), pyr->getXBottom(), pyr->getYBottom(), pyr->getXTop(), pyr->getYTop());
			applyTransformations(*geo, 0);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.CopyHierarchy(*geo);
			delete geo;
			break;
		}
		case 110: {
			x3dTorus* torus = dynamic_cast<x3dTorus*>(Objects[i]);
			CGeoTube* geo = new CGeoTube;
			geo->InitArc(0, torus->getTorusInnerRadius(), torus->getTorusOuterRadius(), torus->getTorusAngle(), NULL);
			geo->Transform(CHMat(1.f, 0.f, 0.f, 0.f, 0.f, float(cos(1.5708)), float(-sin(1.5708)), 0.f, 0.f, float(sin(1.5708)), float(cos(1.5708)), 0.f, 0.f, 0.f, 0.f, 1.f));
			applyTransformations(*geo, 0);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.CopyHierarchy(*geo->CopyToTriangleList());
			delete geo;
			break;
		}
		case 111: {
			x3dDish* dish = dynamic_cast<x3dDish*>(Objects[i]);
			ULDebug("Primitiv \"Dish\" wird noch nicht unterstützt.");
			//implementation of Dish
			break;
		}
		case 112: {
			x3dRectangularTorus* recTorus = dynamic_cast<x3dRectangularTorus*>(Objects[i]);
			CGeoTube* geo = new CGeoTube;
			geo->InitStraight(recTorus->getInnerRadius(), recTorus->getOuterRadius(), recTorus->getHeight(), NULL);
			applyTransformations(*geo, 0);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.CopyHierarchy(*geo->CopyToTriangleList());
			delete geo;
			break;
		}
		case 113: {
			x3dSlopedCylinder* sc = dynamic_cast<x3dSlopedCylinder*>(Objects[i]);
			//implementation of slopedCylinder
			ULDebug("Primitiv \"SlopedCylinder\" wird noch nicht unterstützt.");
			break;
		}
		case 114: {
			x3dSnout* snout = dynamic_cast<x3dSnout*>(Objects[i]);
			//implementation of snout
			ULDebug("Primitiv \"Snout\" wird noch nicht unterstützt.");
			break;
		}
		case 115: {
			x3dSphereSegment* ssg = dynamic_cast<x3dSphereSegment*>(Objects[i]);
			//implementation of spheresegment
			ULDebug("Primitiv \"SphereSegment\" wird noch nicht unterstützt.");
			break;
		}
	}
}

void x3dImporter::addChildShapes(CGeo &geometry, int i)
{
	int spec = Objects[i]->getSpecifier();
	switch (spec) {
		case 100: {
			x3dBox* box = dynamic_cast<x3dBox*>(Objects[i]);
			CGeoCube* geo = new CGeoCube;
			geo->Init(box->getBoxSize()[0], box->getBoxSize()[1], box->getBoxSize()[2], NULL);
			applyTransformations(*geo, i);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.AddGeo(geo);
			//delete geo;
			break;
		}
		case 101: {
			x3dSphere* sphere = dynamic_cast<x3dSphere*>(Objects[i]);
			CGeoSphere* geo = new CGeoSphere;
			geo->Init(sphere->getSphereRadius(), NULL);
			applyTransformations(*geo, i);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.AddGeo(geo->CopyToTriangleList());
			//delete geo;
			break;
		}
		case 102: {
			x3dCone* cone = dynamic_cast<x3dCone*>(Objects[i]);
			CGeoCylinder* geo = new CGeoCylinder;
			geo->Init(cone->getConeBottomRadius(), cone->getConeTopRadius(), cone->getConeHeight(), NULL);
			geo->Transform(CHMat(1, 0, 0, 0, 0, 1, 0, -cone->getConeHeight() / 2, 0, 0, 1, 0, 0, 0, 0, 1));
			applyTransformations(*geo, i);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.AddGeo(geo->CopyToTriangleList());
			//delete geo;
			break;
		}
		case 103: {
			x3dCircle2D* circle = dynamic_cast<x3dCircle2D*>(Objects[i]);
			CGeoCircle2D* geo = new CGeoCircle2D(circle->getCircleRadius(), 360, 0);
			applyTransformations(*geo, i);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.AddGeo(geo);
			//delete geo;
			break;
		}
		case 104: {
			x3dArc2D* arc = dynamic_cast<x3dArc2D*>(Objects[i]);
			CGeoCircle2D* geo = new CGeoCircle2D(arc->getArcRadius(), arc->getDegree(), arc->getStartAngleInDegree());
			applyTransformations(*geo, i);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.AddGeo(geo);
			//delete geo;
			break;
		}
		case 105: {
			x3dArcClose2D* arcclose = dynamic_cast<x3dArcClose2D*>(Objects[i]);
			CGeoArcClose2D* geo = new CGeoArcClose2D(arcclose->getArcClosedRadius(), arcclose->getDegree(), arcclose->getStartAngleInDegree());
			applyTransformations(*geo, i);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.AddGeo(geo->CopyToTriangleList());
			//delete geo;
			break;
		}
		case 106: {
			x3dCylinder* cylinder = dynamic_cast<x3dCylinder*>(Objects[i]);
			CGeoCylinder* geo = new CGeoCylinder;
			geo->Init(cylinder->getCylinderRadius(), cylinder->getCylinderRadius(), cylinder->getCylinderHeight(), NULL);
			geo->Transform(CHMat(1, 0, 0, 0, 0, 1, 0, -cylinder->getCylinderHeight() / 2, 0, 0, 1, 0, 0, 0, 0, 1));
			applyTransformations(*geo, i);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.AddGeo(geo->CopyToTriangleList());
			//delete geo;
			break;
		}
		case 107: {
			x3dDisk2D* disk2d = dynamic_cast<x3dDisk2D*>(Objects[i]);
			CGeoTube* geo = new CGeoTube;
			geo->InitStraight(disk2d->getDiskInnerRadius(), disk2d->getDiskOuterRadius(), 0.01f, NULL);
			geo->Transform(CHMat(1.f, 0.f, 0.f, 0.f, 0.f, float(cos(1.5708)), float(-sin(1.5708)), 0.f, 0.f, float(sin(1.5708)), float(cos(1.5708)), 0.f, 0.f, 0.f, 0.f, 1.f));
			applyTransformations(*geo, i);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.AddGeo(geo->CopyToTriangleList());
			//delete geo;
			break;
		}
		case 108: {
			x3dPlane* plane = dynamic_cast<x3dPlane*>(Objects[i]);
			CGeoQuad* geo = new CGeoQuad;
			geo->Init(plane->getPlaneSize()[0], plane->getPlaneSize()[1], NULL);
			/*
			geo->Transform(CHMat(1, 0, 0, plane->planecenter[0], 0, 1, 0, plane->planecenter[1], 0, 0, 1, plane->planecenter[2], 0, 0, 0, 1));
			*/
			applyTransformations(*geo, i);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.AddGeo(geo->CopyToTriangleList());
			//delete geo;
			break;
		}
		case 109: {
			x3dPyramid* pyr = dynamic_cast<x3dPyramid*>(Objects[i]);
			CGeoPyramid* geo = new CGeoPyramid;
			geo->Initialize(pyr->getHeight(), pyr->getXBottom(), pyr->getYBottom(), pyr->getXTop(), pyr->getYTop());
			applyTransformations(*geo, i);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.AddGeo(geo);
			//delete geo;
			break;
		}
		case 110: {
			x3dTorus* torus = dynamic_cast<x3dTorus*>(Objects[i]);
			CGeoTube* geo = new CGeoTube;
			geo->InitArc(0, torus->getTorusInnerRadius(), torus->getTorusOuterRadius(), torus->getTorusAngle(), NULL);
			geo->Transform(CHMat(1.f, 0.f, 0.f, 0.f, 0.f, float(cos(1.5708)), float(-sin(1.5708)), 0.f, 0.f, float(sin(1.5708)), float(cos(1.5708)), 0.f, 0.f, 0.f, 0.f, 1.f));
			applyTransformations(*geo, i);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.AddGeo(geo->CopyToTriangleList());
			//delete geo;
			break;
		}
		case 111: {
			x3dDish* dish = dynamic_cast<x3dDish*>(Objects[i]);
			ULDebug("Primitiv \"Dish\" wird noch nicht unterstützt.");
			//implementation of Dish
			break;
		}
		case 112: {
			x3dRectangularTorus* recTorus = dynamic_cast<x3dRectangularTorus*>(Objects[i]);
			CGeoTube* geo = new CGeoTube;
			geo->InitStraight(recTorus->getInnerRadius(), recTorus->getOuterRadius(), recTorus->getHeight(), NULL);
			applyTransformations(*geo, i);
			applyColor(*geo, *dynamic_cast<x3dShape*>(Objects[i]));
			geometry.AddGeo(geo->CopyToTriangleList());
			//delete geo;
			break;
		}
		case 113: {
			x3dSlopedCylinder* sc = dynamic_cast<x3dSlopedCylinder*>(Objects[i]);
			//implementation of slopedCylinder
			ULDebug("Primitiv \"SlopedCylinder\" wird noch nicht unterstützt.");
			break;
		}
		case 114: {
			x3dSnout* snout = dynamic_cast<x3dSnout*>(Objects[i]);
			//implementation of snout
			ULDebug("Primitiv \"Snout\" wird noch nicht unterstützt.");
			break;
		}
		case 115: {
			x3dSphereSegment* ssg = dynamic_cast<x3dSphereSegment*>(Objects[i]);
			//implementation of spheresegment
			ULDebug("Primitiv \"SphereSegment\" wird noch nicht unterstützt.");
			break;
		}
	}
}

void x3dImporter::applyTransformations(CGeo & geo, int i)
{
	std::array<float, 16> arr = Objects[i]->getMatrix();
	CHMat mat;
	mat.Init(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8], arr[9], arr[10], arr[11], arr[12], arr[13], arr[14], arr[15]);
	geo.Transform(mat);
}

void x3dImporter::applyTransformationsPlacement(CPlacement &placement, int i)
{
	std::array<float, 16> arr = Objects[i]->getMatrix();
	CHMat mat;
	mat.Init(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5], arr[6], arr[7], arr[8], arr[9], arr[10], arr[11], arr[12], arr[13], arr[14], arr[15]);
	placement.SetMat(mat);
}

void x3dImporter::createModel(CGeo &geometry, bool child, int iterator)
{
	CGeoTriangleTable* table = new CGeoTriangleTable;

	x3dModel* model = dynamic_cast<x3dModel*>(Objects[iterator]);
	std::vector<Vector3D> coordinates = model->getCoordinates();
	std::vector<Vector3D> normalVectors = model->getNormalVectors();
	std::vector<Pair<float, float>> texCoords = model->getTextureCoordinates();

	int sizeCoords = coordinates.size();
	int sizeNormals = normalVectors.size();
	int sizeTexCoords = texCoords.size();

	if (sizeNormals > 0 && sizeTexCoords > 0) {
		for (int i = 0; i < sizeCoords; i++) {
			vertecies.emplace_back();
			vertecies[i].Init(vectorToCHVector(coordinates[i]), vectorToCHVector(normalVectors[i]), CHVector(-1, 0, 0), texCoords[i].getA(), texCoords[i].getB());
		}
	}
	else if (sizeNormals > 0 && sizeTexCoords == 0) {
		for (int i = 0; i < sizeCoords; i++) {
			vertecies.emplace_back();
			vertecies[i].Init(vectorToCHVector(coordinates[i]), vectorToCHVector(normalVectors[i]), CHVector(-1, 0, 0));
		}
	}
	else if (sizeNormals == 0 && sizeTexCoords > 0) {
		for (int i = 0; i < sizeCoords; i++) {
			vertecies.emplace_back();
			vertecies[i].Init(vectorToCHVector(coordinates[i]), CHVector(0, 0, 1, 0), CHVector(-1, 0, 0), texCoords[i].getA(), texCoords[i].getB());
		}
	}
	else {
		for (int i = 0; i < sizeCoords; i++) {
			vertecies.emplace_back();
			vertecies[i].Init(vectorToCHVector(coordinates[i]), CHVector(0, 0, 1, 0), CHVector(-1, 0, 0));
		}
	}
	
	for (int i = 0; i < vertecies.size(); i++) {
		table->AddVertex(&vertecies[i]);
	}

	std::vector<int> indexList = model->getIndexListVec();
	int sizeIndexList = model->getIndexListVec().size();

	for (int i = 0; i < sizeIndexList; i+=3) {
		table->AddIndex(indexList[i]);
		table->AddIndex(indexList[i+1]);
		table->AddIndex(indexList[i+2]);
	}
	table->Init();

	applyTransformations(*table, iterator);
	applyColor(*table, *model);

	if (child == false) {
		geometry.CopyHierarchy(*table->CopyToTriangleList());
	}
	else {
		CGeoTriangleList* geoList = new CGeoTriangleList();
		geoList->CopyHierarchy(*table->CopyToTriangleList());
		geometry.AddGeo(geoList);
	}

	vertecies.clear();
	vertecies.shrink_to_fit();
}

void x3dImporter::createPointList(CGeo & geometry, bool child, int iterator)
{
	CGeoPointList* list = new CGeoPointList();

	x3dPointSet* ps = dynamic_cast<x3dPointSet*>(Objects[iterator]);
	std::vector<Vector3D> coords = ps->getCoords();

	std::vector<CHVector> pos;
	std::vector<CHVector> normals;
	CHVector tangent = CHVector(0,0,1,0);

	for (int i = 0; i < coords.size(); ++i) {
		pos.emplace_back(vectorToCHVector(coords[i]));
		normals.emplace_back(pos[i]);
	}
	for (int i = 0; i < pos.size(); ++i) {
		vertecies.emplace_back();
		vertecies[i].Init(pos[i], normals[i], tangent);
	}
	for (int i = 0; i < vertecies.size(); i++) {
		list->AddVertex(&vertecies[i]);
	}
	list->Init();

	applyTransformations(*list, iterator);
	applyColor(*list, *ps);

	if (child == false) {
		geometry.CopyHierarchy(*list);
	}
	else {
		geometry.AddGeo(list);
	}

	vertecies.clear();
	vertecies.shrink_to_fit();
}

void x3dImporter::createText(CScene &scene, int i)
{
	x3dText* text = dynamic_cast<x3dText*>(Objects[i]);
	std::vector<std::string> strings = text->getStrings();
	float textSize = text->getSize();
	for (int j = 0; j < strings.size(); j++) {
		char *message = new char[strings[j].size() + 1];
		strcpy(message, strings[j].c_str());
		CPlacement* textplace = new CPlacement;
		CWribel* wribel = new CWribel();
		CWritingFont* font = new CWritingFont();

		font->LoadPreset("PrestigeEliteWhite"); //Font is a placeholder. Font is not specificly named in x3d
		font->SetChromaKeyingOn();

		int messageLenght = strings[j].size();
		std::string justA = text->getJustify().getA();
		std::string justB = text->getJustify().getB();
		
		float anchorA = 0;
		float anchorB = 0;

		if (justA == "end") {
			anchorA -= messageLenght /2;
		}
		else if (justA == "middle") {
			anchorA -= messageLenght / 4 + 0.3;
		}
		else if (justA == "first") {
			anchorA = messageLenght *0.01;
		}


		if (justB == "end") {
			anchorB += textSize*1.75;
		}
		else if (justB == "middle") {
			anchorB += textSize / 1.25;
		}
		else if (justB == "first") {
			anchorB += textSize / 1.25;
		}

		//Values were determinated by try n' error. Exact translations don't seem to be possible.
		wribel->Init(CFloatRect(anchorA+0.3, anchorB-0.3, messageLenght / 2 * textSize, textSize), messageLenght, font);
		wribel->m_bBillboard = false;
		
		textplace->AddWribel(wribel);
		scene.AddPlacement(textplace);
		applyTransformationsPlacement(*textplace, i);
		textplace->TranslateDelta(0, -textSize*j, 0);
		wribel->PrintF(message);
	}
}



