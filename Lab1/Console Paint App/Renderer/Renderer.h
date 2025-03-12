#pragma once
#include <iostream>

#include "../Canvas/Canvas.h"
#include "../Menu/Menu.h"



class Renderer {
public:
	Renderer();
	~Renderer();

	void Render();

private:
	Canvas m_canvas;
	Menu m_menu;
};