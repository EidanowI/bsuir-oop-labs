#pragma once
#include "IUser.h"



class User : public IUser {
public:
	User(char* pLogin, unsigned int password_hash);
	User(char* pLogin, unsigned int password_hash, bool perm);
	~User();

	bool TryToLogin(std::string password) override;

	void ChangePermission(IUser* pUser) override;

	void SetPermission(IUser* pUser) override;

	char* GetLogin();
	unsigned int GetPasswordHash();
	bool GetIsCanEdit();

private:
	char m_pLogin[64]{};
	unsigned int m_pasword_hash = 0;
	bool m_isCanEdit = true;
};