#pragma once
#include <vector>
#include <string>
#include "../Content.h"



class TXTImporter {
public:
	TXTImporter();
	~TXTImporter();

	std::vector<Line> ImportFromTxt(std::string& author, std::string& date, std::string path);
};