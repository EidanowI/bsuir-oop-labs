#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <Windows.h>

//time_t a = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
//std::tm* now_tm = std::localtime(&m_openerUser_info->lastTime_changed);
#include "Document.h"
#include "../User/User.h"
#include "Import/TXTImporterAdapter.h"
#include "Command/AddCharCommand.h"
#include "../File/FileDialog.h"
#include "Import/TXTImporterAdapter.h"
#include "Export/Exporters.h"



Document::Document(LocalStorageUserRepo* pUserRepo, User* pUser, const std::string& path) : m_content(true)
{
	m_isEditable = false;

	std::ifstream ifs(path, std::ios::binary);

	int perm_count = 0;
	ifs.read((char*) & perm_count, 4);
	m_permisionLayers = std::vector<EditPermisionLayer>(perm_count);

	
	for (int i = 0; i < perm_count; i++) {
		ifs.read((char*)&m_permisionLayers[i], sizeof(EditPermisionLayer));

		if (m_permisionLayers[i]._login_hash == pUser->GetLoginHash()) {
			m_isEditable = true;
		}
	}



}
Document::Document(LocalStorageUserRepo* pUserRepo, User* pUser) : m_content(true)
{
	m_isEditable = true;

	m_permisionLayers.push_back({ pUser->GetLoginHash(), 0 });
}
Document::~Document() {

}

void Document::PrintAllUsers(LocalStorageUserRepo* pUserRepo) {
	for (auto it = pUserRepo->GetAllUsers().begin(); it != pUserRepo->GetAllUsers().end(); ++it) {
		User* it_pUser = (User*)*it;

		if (it_pUser->IsAdmin()) continue;

		bool is_editor = false;

		for (int i = 0; i < m_permisionLayers.size(); i++) {
			if (it_pUser->GetLoginHash() == m_permisionLayers[i]._login_hash) {
				is_editor = true;
				std::tm* now_tm = std::localtime(&m_permisionLayers[i]._lastTime_edit);
				std::cout << "\033[32m" << it_pUser->GetLogin() << "\033[0m ";
				if (m_permisionLayers[i]._lastTime_edit == 0) {
					std::cout << "(newer edit)\n";
				}
				else {
					
					std::cout << "(" << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S") << ")\n";
				}
			}
		}

		if (!is_editor) {
			std::cout << "\033[31m" << it_pUser->GetLogin() << "\033[0m\n";
		}
	}
}
void Document::ChangePermissionForUser(LocalStorageUserRepo* pUserRepo, User* pUser) {
	for (int i = 0; i < m_permisionLayers.size(); i++) {
		if (pUser->GetLoginHash() == m_permisionLayers[i]._login_hash) {
			m_permisionLayers.erase(m_permisionLayers.begin() + i);

			return;
		}
	}

	m_permisionLayers.push_back({ pUser->GetLoginHash(), 0 });
}

void Document::ImportFromFile() {
	while (true) {
		std::cout << "1. - Import TXT file\n";
		std::cout << "2. - Import MD file\n";
		std::cout << "3. - Import XML file\n";

		char in;
		std::cin >> in;

		IContentImporter* pContent_importer = nullptr;

		if (in == '1') {
			auto path = FileDialog::FileDialogLoad("Import txt", "TXT Files (*.txt)\0*.txt\0");

			pContent_importer = new TXTImporterAdapter();

			m_content = pContent_importer->Import(path);
			m_content.SetIsEditable(m_isEditable);

			delete pContent_importer;

			break;
		}
		else if (in == '2') {
			auto path = FileDialog::FileDialogLoad("Import md", "MD Files (*.md)\0*.md\0");

			break;
		}
		else if (in == '3') {
			auto path = FileDialog::FileDialogLoad("Import xml", "XML Files (*.xml)\0*.xml\0");

			break;
		}
		else {
			std::cout << "Incorrect input!";
		}
	}
}
void Document::ExportToFile() {
	std::string file_path;
	IExporter* pExporter;

	while (true) {
		std::cout << "1. - Export to TXT file\n";
		std::cout << "2. - Export to MD file\n";
		std::cout << "3. - Export to XML file\n";

		char in;
		std::cin >> in;
		
		if (in == '1') {
			file_path = FileDialog::FileDialogSave("Export txt", "TXT Files (*.txt)\0*.txt\0");

			TXTExportFactory factory;
			pExporter = factory.CreateExporter();		

			break;
		}
		else if (in == '2') {
			file_path = FileDialog::FileDialogSave("Export md", "MD Files (*.md)\0*.md\0");

			MDExportFactory factory;
			pExporter = factory.CreateExporter();

			break;
		}
		else if (in == '3') {
			file_path = FileDialog::FileDialogSave("Export xml", "XML Files (*.xml)\0*.xml\0");

			XMLExportFactory factory;
			pExporter = factory.CreateExporter();

			break;
		}
		else {
			std::cout << "Incorrect input!";
		}
	}

	pExporter->Export(m_content, file_path);

	delete pExporter;
}

void Document::SaveDocument(ISaverStrategy* saver) {
	saver->Save(this);
}

void Document::Edit(User* pUser) {
	bool res = m_content.Edit();

	if (res) {
		for (int i = 0; i < m_permisionLayers.size(); i++) {
			if (m_permisionLayers[i]._login_hash == pUser->GetLoginHash()) {
				m_permisionLayers[i]._lastTime_edit = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			}
		}
	}
}