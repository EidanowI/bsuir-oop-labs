#pragma once
#include <string>



class IUser {
public:
	virtual ~IUser() {}

	virtual bool IsAdmin() = 0;

	virtual bool TryToLogin(std::string password) = 0;
};