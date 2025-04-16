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
	char pLogin[64] = "admin";
	m_reg_pUsers.push_back(new Admin(pLogin, Hash("1111")));
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

		delete pUser;
	}

	ofs.close();
}

void LocalStorageUserRepo::LoadRegUsers() {
	std::ifstream ifs(".users.cfg", std::ios::binary | std::ios::ate);
	if (ifs.is_open()) {
		int file_size = ifs.tellg();
		ifs.seekg(0);

		for (int i = 0; i < file_size / 68; i++) {
			char login[64]{};
			unsigned int password_hash;

			ifs.read(login, 64);
			ifs.read((char*)&password_hash, 4);

			m_reg_pUsers.push_back(new User(login, password_hash));
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

	m_reg_pUsers.push_back(new User(pLogin, Hash(password)));
}


User::User(char* pLogin, unsigned int password_hash) : m_pasword_hash(password_hash){
	memcpy(m_pLogin, pLogin, 64);
}
User::~User() {

}

bool User::TryToLogin(std::string password) {
	return m_pasword_hash == Hash(password);
}
void User::ChangePermission(IUser* pUser, bool isAdmin) {
	std::cout << "You dont have permissions!\n";
}

char* User::GetLogin() {
	return m_pLogin;
}
unsigned int User::GetPasswordHash() {
	return m_pasword_hash;
}


Admin::Admin(char* pLogin, unsigned int password_hash) : User(pLogin, password_hash){

}
Admin::~Admin() {

}

void Admin::ChangePermission(IUser* pUser, bool isAdmin) {
	std::cout << "Yaaa Yaaa";
}