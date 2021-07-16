#pragma once
#include "x3dShape.h"
class x3dBox : public x3dShape
{
public:
	x3dBox(int start, std::string infos, int id);
	~x3dBox();

	float * getBoxSize();

private:

	float boxsize[3] = { 1.f, 1.f, 1.f };
};

