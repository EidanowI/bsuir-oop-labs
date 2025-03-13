#pragma once
#include "IFigure.h"


class Rect : public IFigure {
public:
	Rect(int x, int y, int a, int b, char f);
	~Rect();

	void AddToCanvas(char* canvas) override;

	void SaveToFile(std::ofstream& ofs) override;

	int GetSquare() override;
private:

	int m_a;
	int m_b;
};