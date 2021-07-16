/*
Hält und wertet Informationen aus dem <Transformation> Tag aus.
Autor: Lukas Zickl
*/

#pragma once
#include <string>
#include <array>


class Matrix
{
public:
	Matrix(std::string transform);
	~Matrix();

	static std::array<float, 16> multiply(std::array<float, 16> mat, std::array<float, 16> MAT);

	void setStartingLine(int start);
	void setEndingLine(int end);
	int getEndingLine();
	int getStartingLine();
	std::array<float, 16> getMatrix();

private:
	std::array<float, 16> Mat;
	std::array<float, 16> transmat;
	std::array<float, 16> rotmat;
	std::array<float, 16> scalemat;

	int startingLine = 0;
	int endingLine = 0;

	std::string info = "";
};

