//Autor: Lukas Zickl

#pragma once
#include "Vektoria\Root.h"
using namespace Vektoria;

class CGeoCircle2D : public CGeoLineList
{
public:
	CGeoCircle2D(float fRadius, float degree, float startAngle);
	~CGeoCircle2D();

private:
	float degToRad(float angleInDegree);
	CVertex m_avertexCircle[361];
};

