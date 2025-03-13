#pragma once
#include "IFigure.h"


class Elipse : public IFigure{
public:
	Elipse(int x, int y, int a, int b, char f);
	~Elipse();

	void AddToCanvas(char* canvas) override;

	void SaveToFile(std::ofstream& ofs) override;

	int GetSquare() override;
private:

	int m_a;
	int m_b;
};