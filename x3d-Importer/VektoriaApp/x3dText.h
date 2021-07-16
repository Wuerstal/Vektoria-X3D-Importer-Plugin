#pragma once
#include "x3dShape.h"
#include "Pair.h"
class x3dText :
	public x3dShape
{
public:
	x3dText(int start, std::string infos, int id);
	~x3dText();

	std::vector<std::string> getStrings();
	float getSize();
	bool getLeftToRight();
	float getQuality();
	float getSpacing();
	bool getTopToBottom();
	Pair<std::string, std::string> getJustify();
	float getLength();
	float getMaxExtend();
	bool getHorizontal();
	std::string getFamily();

private:

	std::string string;
	std::vector<std::string> strings;
	Pair<std::string, std::string> justify;
	//Parsed-Not-Implemented----------
	float length = NULL;
	float maxExtent = 0;

	float size = 1; //Schriftgrößen verschieben den Text...
	bool leftToRight = true;
	float quality = 0;
	float spacing = 1;
	bool topToBottom = true;
	std::string style = "plain"; //Plain, bold, italic, bolditalic,....
	bool horizontal = true;
	std::string family = "serif";
	//--------------------------------
};

