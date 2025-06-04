#pragma once
#include <vector>
#include <string>



class TXTImporter {
public:
	TXTImporter();
	~TXTImporter();

	std::vector<char> ImportTextFromTxt(const std::string& path);
};