#include "Canvas.h"



Canvas::Canvas() {
    Clear();
}
Canvas::~Canvas() {
    for (int i = 0; i < m_figures.size(); i++) {
        delete m_figures[i];
    }
}

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
        m_figures[i]->AddToCanvas((char*)this);
    }
}

void Canvas::AddFigure(IFigure* figure) {
    m_figures.push_back(figure);
}

void Canvas::DeleteFigure(int index) {
    if (index == -1) return;

    delete m_figures[index];
    m_figures.erase(m_figures.begin() + index);
}
void Canvas::MoveFigure(int index, int x, int y) {
    if (index == -1) return;

   
}
void Canvas::FillFigure(int index, char f) {
    if (index == -1) return;

    m_figures[index]->SetFillChar(f);
}

void Canvas::Save(const LPWSTR& path){}
void Canvas::Load(const LPWSTR& path){}