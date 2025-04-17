#pragma once
#include "IPermissionOpener.h"



class EditPermissionOpener : public IPermissionOpener{
public:
	EditPermissionOpener();
	~EditPermissionOpener();

	void OpenDocument(std::string path) override;
};