#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <map>



class User {
public:
	User(std::string login, std::string password);
	User(std::string login, std::string password, bool isAdmin);

	bool ComparePassword(std::string& password);

	char* GetLogin();

private:
	std::string m_login;
	unsigned int m_pasword_hash;
	bool m_isAdmin;
};

class UserManager {
public:
	static void Init();
	static void Term();

	static bool TryFindUser(std::string login);
	static void Register(std::string login, std::string password);
	static bool Login(std::string login, std::string password);
	static User* GetCurrentUser();
	static void Logout();

private:
	static User* s_currentUser;
	static std::map<unsigned int, User*> s_users;
};