#pragma once
#include <string>
#include "../Content/Content.h"



class IExporter {
public:
	virtual void Export(Content& content, const std::string& path) = 0;
};