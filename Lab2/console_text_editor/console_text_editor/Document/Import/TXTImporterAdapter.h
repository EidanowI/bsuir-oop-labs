#pragma once
#include "IContentImporter.h"
#include "TXTImporter.h"



class TXTImporterAdapter : public IContentImporter{
public:
	TXTImporterAdapter();
	~TXTImporterAdapter();

	//std::vector<Line> Import(std::string& author, std::string& date, std::string path) override;

private:
	TXTImporter* m_importer;
};