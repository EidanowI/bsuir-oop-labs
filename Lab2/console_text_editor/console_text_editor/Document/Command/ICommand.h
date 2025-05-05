#pragma once
#include <vector>
#include "../Content.h"

class Line;

class ICommand {
public:
	virtual ~ICommand(){}

	virtual std::vector<Line> BringToState() = 0;
};