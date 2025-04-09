#pragma once
#include <map>

#include "User.h"



class AuthManager {
public:
	class
private:
	static std::map<unsigned int, User*> s_users;
};