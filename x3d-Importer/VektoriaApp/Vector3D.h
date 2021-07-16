/*
Klasse für einen Vektor. Dient als Schnittstelle zwischen Importer und Vektoria.
Autor: Lukas Zickl
*/

#pragma once
#include <cmath>
class Vector3D
{
public:
	Vector3D(){}
	Vector3D(float a, float b, float c, float d) {
		x = a;
		y = b;
		z = c;
		uv = d;
	}
	float x;
	float y;
	float z;
	float uv;

	Vector3D &operator-=(const Vector3D &vec){
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}

	Vector3D Norm() {
		float a = std::sqrt((x*x) + (y*y) + (z*z));
		if (a > 0) {
			x = x / a;
			y = y / a;
			z = z / a;
		}
		return *this;
	}
	
};

