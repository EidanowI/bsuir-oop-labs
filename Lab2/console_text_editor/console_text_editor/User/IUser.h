#pragma once
#include <string>



class IUser {
public:
	virtual ~IUser() {}

	virtual bool TryToLogin(std::string password) = 0;
};