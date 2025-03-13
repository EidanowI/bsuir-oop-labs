#pragma once

#include <windows.h>
#include <commdlg.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "../Figures/IFigure.h"


#define WIDTH 138
#define HEIGHT 36

class Canvas {
public:
	Canvas();
	~Canvas();

	char* GetScreenBuffer();
	std::vector<IFigure*>& GetFigures() { return m_figures; }

	void Clear();
	void DrawAllFigures();

	void AddFigure(IFigure* figure);

	void DeleteFigure(int index);
	void MoveFigure(int index, int x, int y);
	void FillFigure(int index, char f);

	void Save(const LPWSTR& path);
	void Load(const LPWSTR& path);

private:
	char m_screenBuffer[WIDTH * HEIGHT]{};

	std::vector<IFigure*> m_figures;
};