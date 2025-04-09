#include "User.h"


unsigned int Hash(const std::string& a) {
	unsigned int hash = 5381;
	for (int i = 0; i < a.size(); i++) {
		hash = ((hash << 5) + hash) + a[i];
	}

	return hash;
}


User::User(std::string login, std::string password, bool isAdmin) {
	m_login = login;

	m_pasword_hash = Hash(password);

	m_isAdmin = isAdmin;
}
User::User(std::string login, std::string password) : User::User(login, password, false) {}
User::User(std::string login, unsigned int pasword_hash) {
	m_login = login;

	m_pasword_hash = pasword_hash;

	m_isAdmin = false;
}

bool User::ComparePassword(std::string& password) {
	return m_pasword_hash == Hash(password);
}

char* User::GetLogin() {
	return m_login.data();
}


User* UserManager::s_currentUser = nullptr;
std::map<unsigned int, User*> UserManager::s_users{};

void UserManager::Init() {
	s_users[Hash("admin")] = new User("admin", "1111", true);

	std::ifstream ifs(".users.cfg", std::ios::binary | std::ios::ate);
	if (ifs.is_open()) {
		int file_size = ifs.tellg();
		ifs.seekg(0);

		for (int i = 0; i < file_size / 68; i++) {
			char login[64]{};
			unsigned int password_hash;

			ifs.read(login, 64);
			ifs.read((char*)&password_hash, 4);

			s_users[Hash(login)] = new User(login, password_hash);
		}
	}
	ifs.close();
}
void UserManager::Term() {
	std::ofstream ofs(".users.cfg", std::ios::binary);

	for (const auto& [hash, pUser] : s_users) {
		char login[64]{};

		if (hash != Hash("admin")) {
			for (int i = 0; i < pUser->m_login.size(); i++) {
				login[i] = pUser->m_login[i];
			}
			
			ofs.write(login, 64);
			ofs.write((char*) & pUser->m_pasword_hash, 4);
		}

		delete pUser;
	}

	ofs.close();
}

bool UserManager::TryFindUser(std::string login) {
	return s_users.contains(Hash(login));
}
void UserManager::Register(std::string login, std::string password) {
	s_currentUser = new User(login, password);

	s_users[Hash(login)] = s_currentUser;
}
bool UserManager::Login(std::string login, std::string password) {
	auto login_hash = Hash(login);
	if(s_users.contains(login_hash)){
		if (s_users[login_hash]->ComparePassword(password)) {
			s_currentUser = s_users[login_hash];
			return true;
		}
		else {
			return false;
		}
	}
}
User* UserManager::GetCurrentUser() {
	return s_currentUser;
}
void UserManager::Logout() {
	s_currentUser = nullptr;
}