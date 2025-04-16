#pragma once
#include <list>

#include "User.h"



class Admin : public User {
public:
	Admin(char* pLogin, unsigned int password_hash);
	~Admin();

	void ChangePermission(IUser* pUser, bool isAdmin) override;

private:
	std::list<IUser*> m_administreted_pUsers;
};