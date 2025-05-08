#pragma once
#include <vector>
#include "../Content/Content.h"



class ICommand {
public:
	virtual ~ICommand(){}

	virtual void BringToState(Content* pContent) = 0;
};