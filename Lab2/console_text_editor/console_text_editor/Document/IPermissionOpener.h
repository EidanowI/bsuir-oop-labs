#pragma once
#include <string>



class IPermissionOpener {
public:
	virtual ~IPermissionOpener(){}

	virtual void OpenDocument(std::string path) = 0;
};