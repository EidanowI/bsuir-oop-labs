#pragma once
#include <vector>
#include <string>
//#include "../Content.h"



class IContentImporter {
public:
	virtual ~IContentImporter() {}
	//virtual std::vector<Line> Import(std::string& author, std::string& date, std::string path) = 0;
};