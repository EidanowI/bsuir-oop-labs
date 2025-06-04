#pragma once
#include "IUser.h"



class User : public IUser {
public:
	User(const char* pLogin, unsigned int password_hash);
	~User();

	bool IsAdmin() override;

	bool TryToLogin(std::string password) override;


	char* GetLogin();
	unsigned int GetLoginHash();
	unsigned int GetPasswordHash();

	bool CompareToByLogin(User* pOtherUser);

private:
	char m_pLogin[64]{};
	unsigned int m_pasword_hash = 0;
};