#include "CGeoArcClose2D.h"

CGeoArcClose2D::CGeoArcClose2D(float fRadius, float fDegree, float startAngle)
{
	startAngle += 90;
	float start = degToRad(startAngle);
	m_vertexMiddle.Init(CHVector(0, 0, 0, 1), CHVector(0, 0, 0, 1), CHVector(0, 1, 0, 0),0,1);
	AddVertex(&m_vertexMiddle);
	for (int i = 0; i <= (int)fDegree; ++i) {
		float fr = ((float)i / 360);
		float fa = fr * TWOPI + start;
		CHVector vPos = CHVector(fRadius*sin(fa), -fRadius*cos(fa), 0.0f, 1.0f);
		CHVector vNormal = vPos;
		vNormal.Normal();
		CHVector vTangent = CHVector(0.0f, 1.0f, 0.0f, 0.0f);
		float fu = fr;
		float fv = 0.0f;
		m_avertexArcClose[i].Init(vPos, vNormal, vTangent, fu, fv);
		AddVertex(&m_avertexArcClose[i]);
	}

	for (int i = 0; i < (int)fDegree; ++i) {
		AddIndex(0);
		AddIndex(i+1);
		AddIndex(i+2);
	}
	Init();
}

CGeoArcClose2D::~CGeoArcClose2D()
{
}

float CGeoArcClose2D::degToRad(float angleInDegree)
{
	float degRad = angleInDegree * PI / 180;
	return degRad;
}

