/*#include "TXTImporterAdapter.h"
#include "TXTImporter.h"

#include <fstream>



TXTImporterAdapter::TXTImporterAdapter() {
	m_importer = new TXTImporter();
}
TXTImporterAdapter::~TXTImporterAdapter() {
	delete m_importer;
}

std::vector<Line> TXTImporterAdapter::Import(std::string& author, std::string& date, std::string path) {
	std::vector<Line> ret = m_importer->ImportFromTxt(author, date, path);

	return ret;
}



TXTImporter::TXTImporter() {

}
TXTImporter::~TXTImporter() {

}

std::vector<Line> TXTImporter::ImportFromTxt(std::string& author, std::string& date, std::string path) {
	author = "autor";
	date = "date";

	std::ifstream ifs(path, std::ios::ate|std::ios::binary);

	int file_size = ifs.tellg();

	ifs.seekg(0);

	char* buff = new char[file_size];
	ifs.read(buff, file_size);
	ifs.close();

	char line_content[140]{};

	std::vector<Line> ret;


	int j = 0;
	for (int i = 0; i < file_size; i++) {
		if (j == 140) {
			j = 0;

			Line new_line = Line(line_content);
			ret.push_back(new_line);

			for (int k = 0; k < 140; k++) {
				line_content[k] = 0;
			}
		}

		if (buff[i] == '\n') {
			j = 0;

			Line new_line = Line(line_content);
			ret.push_back(new_line);

			for (int k = 0; k < 140; k++) {
				line_content[k] = 0;
			}

			//i++;
			continue;
		}

		line_content[j] = buff[i];

		j++;
	}

	Line new_line = Line(line_content);
	ret.push_back(new_line);

	delete buff;

	return ret;
}*/