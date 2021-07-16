#include "CGeoPyramid.h"

CGeoPyramid::CGeoPyramid()
{
}

CGeoPyramid::~CGeoPyramid()
{
}

void CGeoPyramid::Initialize(float fHeight, float fWidth, float fDepth, float fXOffset, float fYOffset)
{
	//Normalen vermutlich noch falsch
	CHVector verts[10];
	
	verts[0] = CHVector(fXOffset, fHeight, fYOffset);
	verts[1] = CHVector(-fWidth, -fHeight, fDepth);
	verts[2] = CHVector(fWidth, -fHeight, fDepth);
	verts[3] = CHVector(fWidth, -fHeight, -fDepth);
	verts[4] = CHVector(-fWidth, -fHeight, -fDepth);
	verts[5] = CHVector(-fWidth, -fHeight, -fDepth);
	verts[6] = CHVector(-fWidth, -fHeight, -fDepth);
	verts[7] = CHVector(fWidth, -fHeight, -fDepth);
	verts[8] = CHVector(-fWidth, -fHeight, fDepth);
	verts[9] = CHVector(fWidth, -fHeight, fDepth);


	m_avertex[0].Init(verts[0], CHVector(0, 1, 0, 0), CHVector(-1, 0, 0));
	m_avertex[1].Init(verts[1], CHVector(0, 0, 1, 0), CHVector(-1, 0, 0));
	m_avertex[2].Init(verts[2], CHVector(1, 0, 0, 0), CHVector(-1, 0, 0));
	m_avertex[3].Init(verts[3], CHVector(0, 0, 1, 0), CHVector(-1, 0, 0));
	m_avertex[4].Init(verts[4], CHVector(-1, 0, 0,0), CHVector(-1, 0, 0));
	m_avertex[5].Init(verts[5], CHVector(0, 0, -1,0), CHVector(-1, 0, 0));

	m_avertex[6].Init(verts[6], CHVector(0, -1, 0, 0), CHVector(-1, 0, 0));
	m_avertex[7].Init(verts[7], CHVector(0, -1, 0, 0), CHVector(-1, 0, 0));
	m_avertex[8].Init(verts[8], CHVector(0, -1, 0, 0), CHVector(-1, 0, 0));
	m_avertex[9].Init(verts[9], CHVector(0, -1, 0,0), CHVector(-1, 0, 0));

	AddVertex(&m_avertex[0]);
	AddVertex(&m_avertex[1]);
	AddVertex(&m_avertex[2]);

	AddVertex(&m_avertex[0]);
	AddVertex(&m_avertex[2]);
	AddVertex(&m_avertex[3]);

	AddVertex(&m_avertex[0]);
	AddVertex(&m_avertex[3]);
	AddVertex(&m_avertex[4]);

	AddVertex(&m_avertex[0]);
	AddVertex(&m_avertex[5]);
	AddVertex(&m_avertex[1]);

	AddVertex(&m_avertex[9]);
	AddVertex(&m_avertex[8]);
	AddVertex(&m_avertex[6]);

	AddVertex(&m_avertex[9]);
	AddVertex(&m_avertex[6]);
	AddVertex(&m_avertex[7]);

	Init();
}
