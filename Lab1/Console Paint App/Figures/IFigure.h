#pragma once
#include "../Canvas/Canvas.h"


class IFigure {
public:
	virtual void AddToCanvas(char* canvas) = 0;
	virtual ~IFigure() {}

	virtual int GetSquare() = 0;
protected:
	std::string m_name;
	char m_fillChar;

	int m_x;
	int m_y;
};
