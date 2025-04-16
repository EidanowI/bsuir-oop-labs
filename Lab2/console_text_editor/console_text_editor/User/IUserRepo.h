#pragma once
#include <iostream>

#include "IUser.h"



class IUserRepo {
public:
	virtual ~IUserRepo(){}

	virtual void LoadRegUsers() = 0;

	virtual IUser* GetUser(std::string login) = 0;
};