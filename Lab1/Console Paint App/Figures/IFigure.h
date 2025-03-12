#pragma once
#include "../Canvas/Canvas.h"


class IFigure {
public:
	virtual void AddToCanvas(char* canvas) = 0;
	virtual ~IFigure() {}

protected:
	std::string name;

	int x;
	int y;
};
