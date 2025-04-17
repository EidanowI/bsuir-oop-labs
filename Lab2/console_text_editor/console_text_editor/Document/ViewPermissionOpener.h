#pragma once
#include "IPermissionOpener.h"



class ViewPermissionOpener : public IPermissionOpener {
public:
	ViewPermissionOpener();
	~ViewPermissionOpener();

	void OpenDocument(std::string path) override;
};