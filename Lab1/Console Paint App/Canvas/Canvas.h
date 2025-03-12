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

	void Clear();
	void DrawAllFigures();

	void Save(const LPWSTR& path);
	void Load(const LPWSTR& path);

private:
	char m_screenBuffer[WIDTH * HEIGHT]{};

	std::vector<IFigure> m_figures;
};