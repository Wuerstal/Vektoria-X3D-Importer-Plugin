#include "Matrix.h"
#include <sstream>
#include <algorithm>
#include <vector>
#include "Vector3D.h"


Matrix::Matrix(std::string transform)
{
	this->info = transform;
	if (transform.find("translation") != std::string::npos) {
		std::string translation = transform.substr(transform.find("translation=\"") + 13);
		translation = translation.substr(0, translation.find("\"", 0));

		std::istringstream buf(translation);
		std::istream_iterator<std::string> beg(buf), end;
		std::vector<std::string> tokens(beg, end);

		float tmp[16] = { 1, 0, 0, std::stof(tokens[0]),
						  0, 1, 0, std::stof(tokens[1]),
						  0, 0, 1, std::stof(tokens[2]),
						  0, 0, 0, 1 };

		for (int i = 0; i < 16; i++) {
			this->transmat[i] = tmp[i];
		}

		tokens.clear();
	}
	else {

		float tmp[16] = { 1, 0, 0, 0,
						  0, 1, 0, 0,
						  0, 0, 1, 0,
						  0, 0, 0, 1 };

		for (int i = 0; i < 16; i++) {
			this->transmat[i] = tmp[i];
		}
	}
	
	if (transform.find("rotation") != std::string::npos) {
		std::string rotation = transform.substr(transform.find("rotation=\"") + 10);
		rotation = rotation.substr(0, rotation.find("\"", 0));

		std::istringstream buf(rotation);
		std::istream_iterator<std::string> beg(buf), end;
		std::vector<std::string> tokens(beg, end);

		float fRotation = -1 * std::stof(tokens[3]);
		Vector3D P1 = Vector3D(0, 0, 0, 1);
		Vector3D P2 = Vector3D(std::stof(tokens[0]), std::stof(tokens[1]), std::stof(tokens[2]), 1);

		P1 -= P2;
		P1.Norm();
		float cosfRotationMinus1 = 1 - cos(fRotation);
		float cosfRotation = cos(fRotation);
		float sinfRotation = sin(fRotation);

		float tmp[16] = { cosfRotationMinus1*P1.x*P1.x + cosfRotation, cosfRotationMinus1*P1.x*P1.y - sinfRotation * P1.z, cosfRotationMinus1*P1.x*P1.z + sinfRotation * P1.y, 0,
						  cosfRotationMinus1*P1.x*P1.y + sinfRotation * P1.z, cosfRotationMinus1*P1.y*P1.y + cosfRotation, cosfRotationMinus1*P1.y*P1.z - sinfRotation * P1.x, 0,
						  cosfRotationMinus1*P1.x*P1.z - sinfRotation * P1.y, cosfRotationMinus1*P1.y*P1.z + sinfRotation * P1.x, cosfRotationMinus1*P1.z*P1.z + cosfRotation, 0,
						  0, 0, 0, 1 };

		for (int i = 0; i < 16; i++) {
			this->rotmat[i] = tmp[i];
		}
		tokens.clear();
	}
	else {
		float tmp[16] = { 1, 0, 0, 0,
						  0, 1, 0, 0,
						  0, 0, 1, 0,
						  0, 0, 0, 1 };

		for (int i = 0; i < 16; i++) {
			this->rotmat[i] = tmp[i];
		}
	}
	if (transform.find("scale") != std::string::npos) {
		std::string scale = transform.substr(transform.find("scale=\"") + 7);
		scale = scale.substr(0, scale.find("\"", 0));

		std::istringstream buf(scale);
		std::istream_iterator<std::string> beg(buf), end;
		std::vector<std::string> tokens(beg, end);

		float tmp[16] = { std::stof(tokens[0]), 0, 0, 0,
						  0, std::stof(tokens[1]), 0, 0,
						  0, 0, std::stof(tokens[2]), 0,
						  0, 0, 0, 1 };

		for (int i = 0; i < 16; i++) {
			this->scalemat[i] = tmp[i];
		}
		tokens.clear();
	}
	else {
		float tmp[16] = { 1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1 };
		for (int i = 0; i < 16; i++) {
			this->scalemat[i] = tmp[i];
		}
	}
	
	Mat = multiply(transmat, multiply(rotmat, scalemat));
	this->info = "";
}

Matrix::~Matrix()
{
}

std::array<float, 16> Matrix::multiply(std::array<float, 16> mat, std::array<float, 16> MAT)
{
	float f00 = mat[0] * MAT[0] + mat[1] * MAT[4] + mat[2] * MAT[8] + mat[3] * MAT[12];
	float f01 = mat[0] * MAT[1] + mat[1] * MAT[5] + mat[2] * MAT[9] + mat[3] * MAT[13];
	float f02 = mat[0] * MAT[2] + mat[1] * MAT[6] + mat[2] * MAT[10] + mat[3] * MAT[14];
	float f03 = mat[0] * MAT[3] + mat[1] * MAT[7] + mat[2] * MAT[11] + mat[3] * MAT[15];


	float f10 = mat[4] * MAT[0] + mat[5] * MAT[4] + mat[6] * MAT[8] + mat[7] * MAT[12];
	float f11 = mat[4] * MAT[1] + mat[5] * MAT[5] + mat[6] * MAT[9] + mat[7] * MAT[13];
	float f12 = mat[4] * MAT[2] + mat[5] * MAT[6] + mat[6] * MAT[10] + mat[7] * MAT[14];
	float f13 = mat[4] * MAT[3] + mat[5] * MAT[7] + mat[6] * MAT[11] + mat[7] * MAT[15];

	float f20 = mat[8] * MAT[0] + mat[9] * MAT[4] + mat[10] * MAT[8] + mat[11] * MAT[12];
	float f21 = mat[8] * MAT[1] + mat[9] * MAT[5] + mat[10] * MAT[9] + mat[11] * MAT[13];
	float f22 = mat[8] * MAT[2] + mat[9] * MAT[6] + mat[10] * MAT[10] + mat[11] * MAT[14];
	float f23 = mat[8] * MAT[3] + mat[9] * MAT[7] + mat[10] * MAT[11] + mat[11] * MAT[15];

	float f30 = mat[12] * MAT[0] + mat[13] * MAT[4] + mat[14] * MAT[8] + mat[15] * MAT[12];
	float f31 = mat[12] * MAT[1] + mat[13] * MAT[5] + mat[14] * MAT[9] + mat[15] * MAT[13];
	float f32 = mat[12] * MAT[2] + mat[13] * MAT[6] + mat[14] * MAT[10] + mat[15] * MAT[14];
	float f33 = mat[12] * MAT[3] + mat[13] * MAT[7] + mat[14] * MAT[11] + mat[15] * MAT[15];


	std::array<float, 16> Matrix = { f00, f01, f02, f03,
									 f10, f11, f12, f13,
									 f20, f21, f22, f23, 
									 f30, f31, f32, f33 };

	return Matrix;

}

void Matrix::setStartingLine(int start)
{
	this->startingLine = start;
}

void Matrix::setEndingLine(int end)
{
	this->endingLine = end;
}

int Matrix::getEndingLine()
{
	return this->endingLine;
}

int Matrix::getStartingLine()
{
	return this->startingLine;
}

std::array<float, 16> Matrix::getMatrix()
{
	return this->Mat;
}
