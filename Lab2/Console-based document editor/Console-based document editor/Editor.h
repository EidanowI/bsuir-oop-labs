#pragma once


enum EDITOR_STATE {
	AUTH_MENU,
};

class Editor {
public:
	void Run();

	void DrawAuthMenu();

private:
	EDITOR_STATE m_state;
};