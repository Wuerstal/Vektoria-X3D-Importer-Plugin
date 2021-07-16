#include "Game.h"
#include <fstream>
#include <string>
#include <iostream>


CGame::CGame(void)
{
}

CGame::~CGame(void)
{
}

void CGame::Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash)
{
	//Initialisierungen
	m_zr.Init(psplash);
	m_zf.Init(hwnd, procOS); 
	m_zf.AddDeviceKeyboard(&keyboard);
	m_zv.SetBackfaceCullingOff();
	m_zr.AddFrame(&m_zf);
	m_zf.AddViewport(&m_zv);
	m_zr.AddScene(&m_zs);

	//Import von ganzen Scenen mit Hilfe des x3d-Importers
	importer.importScene("Models/HelloWorld.x3d", m_zgHello, m_zs, Camplaces);
	importer.importScene("Models/chandalier2.x3d", m_zgChandelier, m_zs, Camplaces);
	importer.importScene("Models/Barrel.x3d", m_zgBarrel, m_zs, Camplaces);
	importer.importScene("Models/primitives.x3d", m_zgPrim, m_zs, Camplaces, true);
	importer.importScene("Models/Lantern.x3d", m_zgLantern, m_zs, Camplaces);
	importer.importScene("Models/points.x3d", m_zgPoints, m_zs, Camplaces);

	//Import von ausschließlich Geometrien mit Hilfe des x3d-Importers
	importer.importShape("Models/ALM0019.x3d", m_zgHeart, true);

	testgeo7 = *m_zgBarrel.m_pgeos[0].m_apgeo[0];
	m_zgBarrel.SubGeo(m_zgBarrel.m_pgeos[0].m_apgeo[0]);

	//Kameras initialisieren und zu Szene hinzufügen
	for (int i = 0; i < Camplaces.m_iPlacements; i++) {
		m_zv.InitFull(Camplaces.m_applacement[i]->m_pcameras[0].m_apcamera[0]);
		m_zs.AddPlacement(Camplaces.m_applacement[i]);
	}
	camCount = Camplaces.m_iPlacements - 1;

	//Placements und Geometrien an Szene hängen
	m_zs.AddPlacement(&m_zpBarrel);
	m_zs.AddPlacement(&m_zpHello);
	m_zs.AddPlacement(&m_zpChandelier);
	m_zs.AddPlacement(&m_zpPrim);
	m_zs.AddPlacement(&m_zpHeart);
	m_zs.AddPlacement(&m_zpLantern);
	m_zs.AddPlacement(&m_zpPoints);
	m_zs.AddPlacement(&m_zpSphere7);
	
	m_zpBarrel.AddGeo(&m_zgBarrel);
	m_zpHello.AddGeo(&m_zgHello);
	m_zpChandelier.AddGeo(&m_zgChandelier);
	m_zpPrim.AddGeo(&m_zgPrim);
	m_zpHeart.AddGeo(&m_zgHeart);
	m_zpLantern.AddGeo(&m_zgLantern);
	m_zpPoints.AddGeo(&m_zgPoints);
	m_zpSphere7.AddGeo(&testgeo7);
	m_zpHeart.TranslateDelta(0, -10, 0);
}

void CGame::Tick(float fTime, float fTimeDelta)
{
	m_zpSphere7.RotateDelta(0, 1, 0, 0.002);
	// Hier die Echtzeit-Veränderungen einfügen:
	if (camCount >= 0) {
		keyboard.PlaceWASD(*Camplaces.m_applacement[camSwitch], fTimeDelta, false);
		Camplaces.m_applacement[camSwitch]->SetTranslationSensitivity(10);
		Camplaces.m_applacement[camSwitch]->SetRotationSensitivity(2);
		m_zv.SetCamera(Camplaces.m_applacement[camSwitch]->m_pcameras[0].m_apcamera[0]);

		if (keyboard.KeyDown(DIK_PGUP)) {
			camSwitch++;
			if (camSwitch > camCount)
				camSwitch = 0;
		}
		if (keyboard.KeyDown(DIK_PGDN)) {
			camSwitch--;
			if (camSwitch < 0)
				camSwitch = camCount;
		}
	}
	m_zr.Tick(fTimeDelta);
}

void CGame::Fini()
{
	// Hier die Finalisierung Deiner Vektoria-Objekte einfügen:
}

void CGame::WindowReSize(int iNewWidth, int iNewHeight)
{
	// Windows ReSize wird immer automatisch aufgerufen, wenn die Fenstergröße verändert wurde.
	// Hier kannst Du dann die Auflösung des Viewports neu einstellen:
	m_zf.ReSize(iNewWidth, iNewHeight);
}

