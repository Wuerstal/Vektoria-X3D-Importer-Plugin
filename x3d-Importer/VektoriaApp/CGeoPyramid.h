//Autor: Lukas Zickl

#pragma once

#include "Vektoria\root.h"

using namespace Vektoria;

class CGeoPyramid : public CGeoTriangleList
{
public: 
	CGeoPyramid();
	~CGeoPyramid();

	void Initialize(float fHeight, float fWidth, float fDepth, float fXOffset = 0, float fYOffset = 0);

	CVertex m_avertex[10];
};

