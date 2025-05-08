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
#include "Command/DeleteCommand.h"



Document::Document(LocalStorageUserRepo* pUserRepo, User* pUser, const std::string& path) : m_content(true)
{
	/*for (auto it = pUserRepo->GetAllUsers().begin(); it != pUserRepo->GetAllUsers().end(); ++it) {
		User* it_pUser = (User*)*it;

		if (it_pUser->CompareToByLogin((User*)pUser)) {

		}
		else {

		}
	}*/
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