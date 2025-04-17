#include <fstream>

#include "LocalStorageUserRepo.h"
#include "User.h"
#include "Admin.h"



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
		if (Hash(pUser->GetLogin()) == Hash("admin")) {
			continue;
		}

		ofs.write(pUser->GetLogin(), 64);
		unsigned int hash = pUser->GetPasswordHash();
		ofs.write((char*)&hash, 4);
		bool is_edit_al = pUser->GetIsCanEdit();
		ofs.write((char*)&is_edit_al, 1);

		delete pUser;
	}

	ofs.close();
}

void LocalStorageUserRepo::LoadRegUsers() {
	char pLogin[64] = "admin";
	Admin* pAdmin_user = new Admin(pLogin, Hash("1111"));
	m_reg_pUsers.push_back(pAdmin_user);

	std::ifstream ifs(".users.cfg", std::ios::binary | std::ios::ate);
	if (ifs.is_open()) {
		int file_size = ifs.tellg();
		ifs.seekg(0);

		for (int i = 0; i < file_size / 69; i++) {
			char login[64]{};
			unsigned int password_hash;
			bool is_edit_al;

			ifs.read(login, 64);
			ifs.read((char*)&password_hash, 4);
			ifs.read((char*)&is_edit_al, 1);

			auto pUser = new User(login, password_hash, is_edit_al);
			m_reg_pUsers.push_back(pUser);

			pAdmin_user->AddAdministretedUser(pUser);
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
void LocalStorageUserRepo::LogAllUsers() {
	for (auto it = m_reg_pUsers.begin(); it != m_reg_pUsers.end(); ++it) {
		User* pUser = (User*)*it;

		if (pUser == GetUser("admin")) continue;

		std::cout << (pUser->GetIsCanEdit() ? "\033[32m" : "\033[31m") << pUser->GetLogin() << "\033[0m\n";
	}
}
void LocalStorageUserRepo::AddNewUser(std::string login, std::string password) {
	char pLogin[64]{};
	memcpy(pLogin, login.c_str(), login.size());

	auto new_user = new User(pLogin, Hash(password));
	m_reg_pUsers.push_back(new_user);

	Admin* admin = (Admin*)GetUser("admin");
	admin->AddAdministretedUser(new_user);
}


User::User(char* pLogin, unsigned int password_hash) : m_pasword_hash(password_hash){
	memcpy(m_pLogin, pLogin, 64);
	m_isCanEdit = true;
}
User::User(char* pLogin, unsigned int password_hash, bool perm) : m_pasword_hash(password_hash) {
	memcpy(m_pLogin, pLogin, 64);
	m_isCanEdit = perm;
}
User::~User() {

}

bool User::TryToLogin(std::string password) {
	return m_pasword_hash == Hash(password);
}
void User::ChangePermission(IUser* pUser) {
	std::cout << "You cant change permissions\n";
}
void User::SetPermission(IUser* pUser) {
	if (Hash(m_pLogin) != Hash(((User*)pUser)->GetLogin())) return;

	m_isCanEdit = (m_isCanEdit ? false : true);
}

char* User::GetLogin() {
	return m_pLogin;
}
unsigned int User::GetPasswordHash() {
	return m_pasword_hash;
}
bool User::GetIsCanEdit() {
	return m_isCanEdit;
}


Admin::Admin(char* pLogin, unsigned int password_hash) : User(pLogin, password_hash){

}
Admin::~Admin() {

}

void Admin::ChangePermission(IUser* pUser) {
	for (auto it = m_administreted_pUsers.begin(); it != m_administreted_pUsers.end(); ++it) {
		((IUser*)*it)->SetPermission(pUser);
	}
}

void Admin::AddAdministretedUser(IUser* pUser) {
	m_administreted_pUsers.push_back(pUser);
}