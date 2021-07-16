#pragma once
#include "Vektoria\Root.h"
using namespace Vektoria;


class CGeoArcClose2D : public CGeoTriangleStrip
{
public:
	//fRadius in float, Degree in °, startAngle in °
	CGeoArcClose2D(float fRadius, float degree, float startAngle);
	~CGeoArcClose2D();

private:
	CVertex m_avertexArcClose[361];
	CVertex m_vertexMiddle;

	float degToRad(float angleInDegree);
};

