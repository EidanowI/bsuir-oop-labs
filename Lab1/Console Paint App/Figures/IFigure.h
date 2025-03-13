#pragma once
#include "../Canvas/Canvas.h"


class IFigure {
public:
	virtual void AddToCanvas(char* canvas) = 0;
	virtual ~IFigure() {}

	virtual int GetSquare() = 0;
	std::string GetName() { return m_name; }
	void SetFillChar(char f) { m_fillChar = f; }
	void Move(int x, int y) { m_x += x; m_y += y; }
protected:
	std::string m_name;
	char m_fillChar;

	int m_x;
	int m_y;
};
