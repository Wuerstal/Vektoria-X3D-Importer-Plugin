#pragma once


#ifdef _WIN64
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug64.lib")
#pragma comment (lib, "VektoriaMath_Debug64.lib")
#else
#pragma comment (lib, "Vektoria_Release64.lib")
#pragma comment (lib, "VektoriaMath_Release64.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment (lib, "Vektoria_Debug.lib")
#pragma comment (lib, "VektoriaMath_Debug.lib")
#else
#pragma comment (lib, "Vektoria_Release.lib")
#pragma comment (lib, "VektoriaMath_Release.lib")
#endif
#endif


#include "Vektoria\Root.h"
#include "x3dImporter.h"

using namespace Vektoria;


class CGame
{
public:
	CGame(void);																				// Wird vor Begin einmal aufgerufen (Konstruktor)
	~CGame(void);																				// Wird nach Ende einmal aufgerufen (Destruktor)

	void Init(HWND hwnd, void(*procOS)(HWND hwnd, unsigned int uWndFlags), CSplash * psplash);	// Wird zu Begin einmal aufgerufen
	void Tick(float fTime, float fTimeDelta);													// Wird während der Laufzeit bei jedem Bildaufbau aufgerufen
	void Fini();																				// Wird am Ende einmal aufgerufen

	void WindowReSize(int iNewWidth, int iNewHeight);											// Wird immer dann aufgerufen, wenn der Benutzer die Fenstergröße verändert hat

private:
    // Hier ist Platz für Deine Vektoriaobjekte:
	CRoot m_zr;
	CScene m_zs;
	CPlacement m_zpCamera;
	CPlacements Camplaces;

	CPlacement m_zpBarrel;
	CGeo m_zgBarrel;
	CPlacement m_zpHello;
	CGeo m_zgHello;
	CPlacement m_zpChandelier;
	CGeo m_zgChandelier;
	CPlacement m_zpPrim;
	CGeo m_zgPrim;
	CPlacement m_zpHeart;
	CGeo m_zgHeart;
	CPlacement m_zpLantern;
	CGeo m_zgLantern;
	CPlacement m_zpPoints;
	CGeo m_zgPoints;
	CPlacement m_zpSphere7;
	CGeo testgeo7;

	//CLightParallel light;

	x3dImporter importer;

	CFrame m_zf;
	CViewport m_zv;

	CDeviceKeyboard keyboard;

	int camSwitch = 0;
	int camCount = 0;
};


