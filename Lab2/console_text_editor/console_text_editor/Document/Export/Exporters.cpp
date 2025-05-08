#include "Exporters.h"
#include <fstream>
#include "../Content/Content.h"



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

}