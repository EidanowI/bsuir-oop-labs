#include <fstream>

#include "LocalStorageUserRepo.h"
#include "User.h"
#include "Admin.h"

#include "../Document/EditPermissionOpener.h"
#include "../Document/ViewPermissionOpener.h"



unsigned int Hash(const std::string& a) {
	unsigned int hash = 5381;
	for (int i = 0; i < a.size(); i++) {
		hash = ((hash << 5) + hash) + a[i];
	}

	return hash;
}


LocalStorageUserRepo::LocalStorageUserRepo() {
	
}
LocalStorageUserRepo::~LocalStorageUserRepo() {
	std::ofstream ofs(".users.cfg", std::ios::binary);

	for (auto it = m_reg_pUsers.begin(); it != m_reg_pUsers.end(); ++it) {
		User* pUser = (User*)*it;
		if (pUser->IsAdmin()) {
			continue;
		}

		ofs.write(pUser->GetLogin(), 64);
		unsigned int hash = pUser->GetPasswordHash();
		ofs.write((char*)&hash, 4);

		delete pUser;
	}

	ofs.close();
}

void LocalStorageUserRepo::LoadRegUsers() {
	Admin* pAdmin_user = new Admin();
	m_reg_pUsers.push_back(pAdmin_user);

	std::ifstream ifs(".users.cfg", std::ios::binary | std::ios::ate);
	if (ifs.is_open()) {
		int file_size = ifs.tellg();
		ifs.seekg(0);

		for (int i = 0; i < file_size / 68; i++) {
			char login[64]{};
			unsigned int password_hash;

			ifs.read(login, 64);
			ifs.read((char*)&password_hash, 4);

			auto pUser = new User(login, password_hash);
			m_reg_pUsers.push_back(pUser);
		}
	}
	ifs.close();
}

IUser* LocalStorageUserRepo::GetUser(std::string login) {
	unsigned int login_hash = Hash(login);

	for (auto it = m_reg_pUsers.begin(); it != m_reg_pUsers.end(); ++it) {
		User* pUser = (User*)*it;

		unsigned int it_login_hash = Hash(pUser->GetLogin());

		if (login_hash == Hash(pUser->GetLogin())) return pUser;
	}

	return nullptr;
}

void LocalStorageUserRepo::AddNewUser(std::string login, std::string password) {
	char pLogin[64]{};
	memcpy(pLogin, login.c_str(), login.size());

	auto new_user = new User(pLogin, Hash(password));
	m_reg_pUsers.push_back(new_user);
}


User::User(const char* pLogin, unsigned int password_hash) : m_pasword_hash(password_hash) {
	memcpy(m_pLogin, pLogin, 64);
}
User::~User() {
}

bool User::IsAdmin() {
	return Hash("admin") == Hash(m_pLogin);
}
bool User::TryToLogin(std::string password) {
	return m_pasword_hash == Hash(password);
}

char* User::GetLogin() {
	return m_pLogin;
}
unsigned int User::GetPasswordHash() {
	return m_pasword_hash;
}


Admin::Admin() : User("admin", Hash("1111")) {

}
Admin::~Admin() {

}