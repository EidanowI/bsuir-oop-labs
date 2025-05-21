#include "Exporters.h"
#include <fstream>
#include "../Content/Content.h"
#include "json.hpp"
#include <sstream>
#include "tinyxml2.h"



TXTExportFactory::TXTExportFactory() {

}
TXTExportFactory::~TXTExportFactory() {

}

IExporter* TXTExportFactory::CreateExporter(){
	return new TXTExporter();
}


TXTExporter::TXTExporter() {

}
TXTExporter::~TXTExporter() {

}

void TXTExporter::Export(Content& content, const std::string& path) {
	std::ofstream ofs(path);

	ofs.write(content.GetData().data(), content.GetData().size());

	ofs.close();
}


MDExportFactory::MDExportFactory() {

}
MDExportFactory::~MDExportFactory() {

}

IExporter* MDExportFactory::CreateExporter() {
	return new MDExporter();
}


MDExporter::MDExporter() {

}
MDExporter::~MDExporter() {

}

void MDExporter::Export(Content& content, const std::string& path) {
	std::ofstream ofs(path);

    for (int i = 0; i < content.cursor_pos; i++) {
        content.m_pFormator->CharDecorate(i, ofs);
        ofs << content.m_data[i];
    }

    for (int i = content.cursor_pos; i < content.m_data.size(); i++) {
		content.m_pFormator->CharDecorate(i, ofs);
        ofs << content.m_data[i];
    }

	ofs.close();
}


JSONExportFactory::JSONExportFactory() {

}
JSONExportFactory::~JSONExportFactory() {

}

IExporter* JSONExportFactory::CreateExporter() {
	return new JSONExporter();
}


JSONExporter::JSONExporter() {

}
JSONExporter::~JSONExporter() {

}

void JSONExporter::Export(Content& content, const std::string& path) {
	nlohmann::json obj;
	std::stringstream strstr;

	for (int i = 0; i < content.cursor_pos; i++) {
		content.m_pFormator->CharDecorate(i, strstr);
		strstr << content.m_data[i];
	}

	for (int i = content.cursor_pos; i < content.m_data.size(); i++) {
		content.m_pFormator->CharDecorate(i, strstr);
		strstr << content.m_data[i];
	}

	obj["content"] = strstr.str().c_str();
	std::ofstream outputFile(path);
	if (outputFile.is_open())
	{
		outputFile << obj.dump(4);
		outputFile.close();
	}
	else throw std::invalid_argument("Can`t create/open json file");
}


XMLExportFactory::XMLExportFactory() {

}
XMLExportFactory::~XMLExportFactory() {

}

IExporter* XMLExportFactory::CreateExporter() {
	return new XMLExporter();
}


XMLExporter::XMLExporter() {

}
XMLExporter::~XMLExporter() {

}

void XMLExporter::Export(Content& content, const std::string& path) {
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement* root = doc.NewElement("Document");

	std::stringstream strstr;

	for (int i = 0; i < content.cursor_pos; i++) {
		content.m_pFormator->CharDecorate(i, strstr);
		strstr << content.m_data[i];
	}

	for (int i = content.cursor_pos; i < content.m_data.size(); i++) {
		content.m_pFormator->CharDecorate(i, strstr);
		strstr << content.m_data[i];
	}


	std::stringstream strstr_line;
	
	for (int i = 0; i < strstr.str().size(); i++) {
		if (strstr.str()[i] == '\n') {
			tinyxml2::XMLElement* lineElement = doc.NewElement("Line");
			lineElement->SetText(strstr_line.str().c_str());
			root->InsertEndChild(lineElement);
			strstr_line = std::stringstream();
		}
		else {
			strstr_line << strstr.str()[i];
		}
	}
	tinyxml2::XMLElement* lineElement = doc.NewElement("Line");
	lineElement->SetText(strstr_line.str().c_str());
	root->InsertEndChild(lineElement);
	strstr_line = std::stringstream();


	doc.InsertEndChild(root);

	if (doc.SaveFile(path.c_str()) != tinyxml2::XML_SUCCESS)
		throw std::invalid_argument("Can`t create/edit xml file");
}