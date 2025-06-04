#pragma once
#include <string>
#include <fstream>
#include "../File/FileDialog.h"
#include "../Document/Document.h"



class ISaverStrategy {
public:
	virtual void Save(const std::string& path) = 0;
};


class CloudStrategy : public ISaverStrategy {
public:
	void Save(const std::string& path) {
		std::ifstream ifs("Docs/" + path + ".lab2");
		std::ofstream ofs("Docs/" + path + ".txt", std::ios::ate);
		int size = ifs.tellg();
		char* buf = new char(size);
		ifs.seekg(0);
		ifs.read(buf, size);


		ofs.write(buf, size);
		ofs.close();
		ifs.close();
		

		system(("python Clouder.py Docs/"  + path + ".txt").c_str());
	}
};
