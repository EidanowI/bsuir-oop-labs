#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>

#include "EditPermissionOpener.h"
#include "ViewPermissionOpener.h"
#include "Document.h"

#include "Import/TXTImporterAdapter.h"



EditPermissionOpener::EditPermissionOpener() {

}
EditPermissionOpener::~EditPermissionOpener() {

}

void EditPermissionOpener::OpenDocumentContext(std::string path, char* opener) {
	Document* edit_document = new Document(true, opener);

	edit_document->Open(path);

	while (true) {
		std::cout << path << "\033[32m (Editable)\033[0m\n";
		std::cout << "1. - Edit\n";
		std::cout << "2. - Save\n";
		std::cout << "3. - Quit\n";

		char in;
		std::cin >> in;

		if (in == '1') {
			edit_document->Edit();
		}
		else if (in == '2') {
			edit_document->Save();
		}
		else if (in == '3') {
			break;
		}
		else {
			std::cout << "Invalid value!";
		}
	}

	delete edit_document;
}


ViewPermissionOpener::ViewPermissionOpener() {

}
ViewPermissionOpener::~ViewPermissionOpener() {

}

void ViewPermissionOpener::OpenDocumentContext(std::string path, char* opener) {
	if (std::filesystem::exists(path)) {
		Document* view_document = new Document(false, opener);

		view_document->Open(path);

		while (true) {
			std::cout << path << "\033[31m (View-only)\033[0m\n";
			std::cout << "1. - Edit\n";
			std::cout << "2. - Save\n";
			std::cout << "3. - Quit\n";

			char in;
			std::cin >> in;

			if (in == '1') {
				view_document->Edit();
			}
			else if (in == '2') {
				view_document->Save();
			}
			else if (in == '3') {
				break;
			}
			else {
				std::cout << "Invalid value!";
			}
		}

		delete view_document;
	}
	else {
		std::cout << "\033[31m" << "File does not exist. So viewer cant creates files." << "\033[0m\n";
	}
}


Document::Document(bool is_editable, char* opener) : m_isEditable(is_editable), m_opener(opener), m_content(m_isEditable){
	//m_isDocument_content_changed = false;
}
Document::~Document() {

}

void Document::Open(std::string name) {
	if (std::filesystem::exists(name)) {
		std::vector<Line> imported_lines;

		if (name[name.size() - 1] == 't') {
			auto pImporter = new TXTImporterAdapter();
			imported_lines = pImporter->Import(m_author, m_edit_date, name);
		}

		for (int i = 0; i < imported_lines.size(); i++) {
			m_content.AddLine(imported_lines[i]);
		}
	}
	else {
		char a[] = "Hello wordls!";
		m_content.AddLine(Line(a));
	}
}
void Document::Save() {
	std::cout << "SAVE";
}
void Document::Edit() {
	bool is_should = m_content.Edit();

	if (is_should) {
		m_author = m_opener;

		auto a = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::tm* now_tm = std::localtime(&a);

		std::ostringstream oss;
		oss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");

		m_edit_date = oss.str();
	}
}

std::string& Document::GetAuthor() {
	return m_opener;
}
std::string& Document::GetEditDate() {
	return m_edit_date;
}