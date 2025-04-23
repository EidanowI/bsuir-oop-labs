#pragma once
#include <string>



class IUser {
public:
	virtual ~IUser() {}

	virtual void OpenDocumentContext(std::string path, char* opener) = 0;

	virtual bool TryToLogin(std::string password) = 0;

	virtual void ChangePermission(IUser* pUser) = 0;

	virtual void SetPermission(IUser* pUser) = 0;
};