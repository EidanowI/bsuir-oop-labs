#pragma once
#include <vector>
#include <string>

#include "../Content/Content.h"



class IContentImporter {
public:
	virtual ~IContentImporter() {}

	virtual Content Import(const std::string& path) = 0;
};