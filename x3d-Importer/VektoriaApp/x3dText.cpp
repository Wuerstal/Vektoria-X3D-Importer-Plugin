#include "x3dText.h"

x3dText::x3dText(int start, std::string infos, int id) {
	
	this->startingLine = start;
	this->specifier = id;
	setGeneral(infos);
	if (infos.find("string") != std::string::npos) {
		this->string = infos.substr(infos.find("string=\"") + 9);
		this->string = this->string.substr(0, this->string.find(">", 0));
		std::string word = "";
		for (int i = 0; i <= this->string.size(); ++i) {
			if (this->string[i] == '\"') {
				if (word == "") {
					continue;
				}
				if (word == " ") {
					word = "";
					continue;
				}
				this->strings.emplace_back(word);
				word = "";
				continue;
			}
			else {
				word += this->string[i];
			}
		}
		char tmp = '\"';
		for (int i = 0; i < this->strings.size(); i++) {
			for (int j = 0; j < this->strings[i].size(); j++) {
				if (this->strings[i].at(j) == 92) {
					this->strings[i].at(j) = tmp;
				}
			}
		}
	}
	if (infos.find("size") != std::string::npos) {
		this->size = extractFloat("size", infos);
	}
	if (infos.find("quality") != std::string::npos) {
		this->quality = extractFloat("quality", infos);
	}
	if (infos.find("spacing") != std::string::npos) {
		this->spacing = extractFloat("spacing", infos);
	}
	if (infos.find("style") != std::string::npos) {
		this->style = extractString("style", infos);
	}
	if (infos.find("justify") != std::string::npos) {
		std::string just = infos.substr(infos.find("justify=\"") + 10);
		std::string justA = just.substr(0, just.find("\"",0));
		this->justify.setA(justA);
		just = just.substr(just.find(justA) + justA.size());
		std::string word = "";
		std::string justB = "";
		for (int i = 0; i <= just.size(); ++i) {
			if (just[i] == '\"') {
				if (word == "") {
					continue;
				}
				if (word == " ") {
					word = "";
					continue;
				}
				justB = word;
				word = "";
				break;
			}
			else {
				word += just[i];
			}
		}
		this->justify.setB(justB);
	}
	else {
		this->justify.setAB("begin", "first");
	}

	if (infos.find("length") != std::string::npos) {
		this->length = extractFloat("length", infos);
	}
	if (infos.find("maxextent") != std::string::npos) {
		this->maxExtent = extractFloat("maxextent", infos);
	}
	if (infos.find("family") != std::string::npos) {
		this->family = extractString("family", infos);
	}
	infos.erase(std::remove(infos.begin(), infos.end(), ' '), infos.end());
	if (infos.find("lefttoright=\"false\"") != std::string::npos) {
		this->leftToRight = false;
	}
	if (infos.find("toptobottom=\"false\"") != std::string::npos) {
		this->topToBottom = false;
	}
	if (infos.find("horizontal=\"false\"") != std::string::npos) {
		this->horizontal = false;
	}
}

x3dText::~x3dText()
{
}

std::vector<std::string> x3dText::getStrings()
{
	return this->strings;
}

float x3dText::getSize()
{
	return this->size;
}

bool x3dText::getLeftToRight()
{
	return this->leftToRight;
}

float x3dText::getQuality()
{
	return this->quality;
}

float x3dText::getSpacing()
{
	return this->spacing;
}

bool x3dText::getTopToBottom()
{
	return this->topToBottom;
}

Pair<std::string, std::string> x3dText::getJustify()
{
	return this->justify;
}

float x3dText::getLength()
{
	return this->length;
}

float x3dText::getMaxExtend()
{
	return this->maxExtent;
}

bool x3dText::getHorizontal()
{
	return this->horizontal;
}

std::string x3dText::getFamily()
{
	return this->family;
}
