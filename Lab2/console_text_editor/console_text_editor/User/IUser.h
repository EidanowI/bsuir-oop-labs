#pragma once



class IUser {
public:
	virtual ~IUser() {}

	virtual bool TryToLogin(std::string password) = 0;
};