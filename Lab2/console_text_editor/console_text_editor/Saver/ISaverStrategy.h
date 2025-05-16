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

	}
};
