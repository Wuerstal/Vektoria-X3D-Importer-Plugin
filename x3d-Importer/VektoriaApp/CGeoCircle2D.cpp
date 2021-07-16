#include "CGeoCircle2D.h"

CGeoCircle2D::CGeoCircle2D(float fRadius, float fDegree, float startAngle)
{
	startAngle += 90;
	float start = degToRad(startAngle);
	for (int i = 0; i <= fDegree; ++i) {
		float fr = ((float)i / 360);
		float fa = fr * TWOPI + start;
		CHVector vPos = CHVector(fRadius*sin(fa), -fRadius*cos(fa), 0.0f, 1.0f);
		CHVector vNormal = vPos;
		vNormal.Normal();
		CHVector vTangent = CHVector(0.0f, 1.0f, 0.0f, 0.0f);
		float fu = fr;
		float fv = 0.0f;
		m_avertexCircle[i].Init(vPos, vNormal, vTangent, fu, fv);
		AddVertex(&m_avertexCircle[i]);
		if (i > 0 && i <= fDegree)
			AddVertex(&m_avertexCircle[i]);
	}
	Init();
}

CGeoCircle2D::~CGeoCircle2D()
{
}

float CGeoCircle2D::degToRad(float angleInDegree)
{
	float degRad = angleInDegree * PI / 180;
	return degRad;
}
