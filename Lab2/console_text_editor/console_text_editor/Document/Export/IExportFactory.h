#pragma once
#include "IExporter.h"



class IExportFactory {
public:
	virtual IExporter* CreateExporter() = 0;
};