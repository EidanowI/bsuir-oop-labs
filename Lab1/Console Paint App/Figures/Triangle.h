#pragma once
#include "IFigure.h"


class Triangle : public IFigure {
public:
	Triangle(int x, int y, int a, int b, char f);
	~Triangle();

	void AddToCanvas(char* canvas) override;

	int GetSquare() override;
private:

	int m_a;
	int m_b;

};