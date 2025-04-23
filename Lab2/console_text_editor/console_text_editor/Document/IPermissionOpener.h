#pragma once
#include <string>



class IPermissionOpener {
public:
	virtual ~IPermissionOpener(){}

	virtual void OpenDocumentContext(std::string path, char* opener) = 0;
};