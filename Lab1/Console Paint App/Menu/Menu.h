#pragma once
#include <iostream>
#include "../Canvas/Canvas.h"



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

	void AddOutputMsg(const std::string& msg);

	void InputChoosingAction();

	LPWSTR FileDialogWindow(LPCWSTR title);

private:
	Canvas* m_pCanvas;
	MENU_STATE m_state = CHOOSING_ACTION;
	std::string m_output_msg;
};