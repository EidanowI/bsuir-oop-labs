#pragma once
#include "IUser.h"



class User : public IUser {
public:
	User(char* pLogin, unsigned int password_hash);
	~User();

	bool TryToLogin(std::string password) override;

	void ChangePermission(IUser* pUser, bool isAdmin) override;

	char* GetLogin();
	unsigned int GetPasswordHash();

private:
	char m_pLogin[64]{};
	unsigned int m_pasword_hash = 0;
};