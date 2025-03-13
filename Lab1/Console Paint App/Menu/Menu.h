#pragma once
#include <iostream>
#include <string>

#include "../Canvas/Canvas.h"
#include "../Figures/Ellipse.h"
#include "../Figures/Rect.h"
#include "../Figures/Triangle.h"

#include "../Utils/ParamsValidator.h"



enum MENU_STATE {
	CHOOSING_ACTION,
	INPUT_DRAW_COMMAND,
	CHOOSING_OBJECT,
	DELETE_OBJECT,
	MOVE_OBJECT,
};

class Menu {
public:

	void DrawMenu();

	void SetCanvas(Canvas* pCanvas);

private:
	void DrawOutput();

	void InputFigureParams(char figure);

	void AddOutputMsg(const std::string& msg);

	void InputChoosingAction();
	int InputSelection();

	LPWSTR FileDialogWindow(LPCWSTR title);

private:
	Canvas* m_pCanvas;
	MENU_STATE m_state = CHOOSING_ACTION;
	std::string m_output_msg;
};