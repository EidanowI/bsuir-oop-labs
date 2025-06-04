#include "TXTImporterAdapter.h"
#include "TXTImporter.h"

#include <fstream>



TXTImporterAdapter::TXTImporterAdapter() {
	m_importer = new TXTImporter();
}
TXTImporterAdapter::~TXTImporterAdapter() {
	delete m_importer;
}

Content TXTImporterAdapter::Import(const std::string& path) {
	auto text_data = m_importer->ImportTextFromTxt(path);

	Content content = Content(false, text_data);

	return content;
}



TXTImporter::TXTImporter() {

}
TXTImporter::~TXTImporter() {

}

std::vector<char> TXTImporter::ImportTextFromTxt(const std::string& path){
	std::ifstream ifs(path, std::ios::ate|std::ios::binary);

	int file_size = ifs.tellg();

	ifs.seekg(0);

	std::vector<char> ret = std::vector<char>(file_size);

	ifs.read(ret.data(), file_size);
	ifs.close();


	return ret;
}