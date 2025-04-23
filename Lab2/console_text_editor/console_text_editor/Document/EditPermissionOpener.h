#pragma once
#include "IPermissionOpener.h"



class EditPermissionOpener : public IPermissionOpener{
public:
	EditPermissionOpener();
	~EditPermissionOpener();

	void OpenDocumentContext(std::string path, char* opener) override;
};