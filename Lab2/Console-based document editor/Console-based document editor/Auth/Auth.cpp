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

bool User::ComparePassword(std::string& password) {
	return m_pasword_hash == Hash(password);
}


User* UserManager::s_currentUser = nullptr;
std::map<unsigned int, User*> UserManager::s_users{};

void UserManager::Init() {
	s_users[Hash("admin")] = new User("admin", "1111", true);

	///
}
void UserManager::Term() {
	for (const auto& [hash, pUser] : s_users) {
		delete pUser;
	}
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