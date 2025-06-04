#pragma once
#include "IContentImporter.h"
#include "TXTImporter.h"



class TXTImporterAdapter : public IContentImporter{
public:
	TXTImporterAdapter();
	~TXTImporterAdapter();

	Content Import(const std::string& path);

private:
	TXTImporter* m_importer;
};