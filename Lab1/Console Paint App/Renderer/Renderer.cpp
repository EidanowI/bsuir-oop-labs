#include "Renderer.h"
#include "../Figures/Ellipse.h"


Renderer::Renderer() {
	m_canvas.Clear();

	m_menu.SetCanvas(&m_canvas);
}
Renderer::~Renderer() {

}

void Renderer::Render() {
	m_canvas.Clear();
	m_canvas.DrawAllFigures();

	std::cout << "\n";
	for (int i = 0; i < HEIGHT + 1; i++) {
		for (int j = 0; j < WIDTH + 2; j++) {
			if (i == 0 || i == HEIGHT || j == 0 || j == WIDTH + 1)
				std::cout << "\x1B[31m#\033[0m";
			else {
				if (!m_canvas.GetScreenBuffer()[(i - 1) * WIDTH + (j - 1)]) {
					std::cout << ' ';
				}
				else
				{
					std::cout << m_canvas.GetScreenBuffer()[(i - 1) * WIDTH + (j -1)];
				}
			}

		}
		std::cout << '\n';
	}

	m_menu.DrawMenu();
}