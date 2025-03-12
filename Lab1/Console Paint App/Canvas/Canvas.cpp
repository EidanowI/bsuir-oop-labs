#include "Canvas.h"



Canvas::Canvas() {
    Clear();
}
Canvas::~Canvas() {}

char* Canvas::GetScreenBuffer() {
	return m_screenBuffer;
}

void Canvas::Clear() {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        m_screenBuffer[i] = ' ';
    }
}
void Canvas::DrawAllFigures() {
    if (m_figures.empty()) return;

    for (int i = 0; i < m_figures.size(); i++) {
        m_figures[i].AddToCanvas((char*)this);
    }
}


void Canvas::Save(const LPWSTR& path){}
void Canvas::Load(const LPWSTR& path){}