#pragma once
#include "IPermissionOpener.h"



class ViewPermissionOpener : public IPermissionOpener {
public:
	ViewPermissionOpener();
	~ViewPermissionOpener();

	void OpenDocumentContext(std::string path, char* opener) override;
};