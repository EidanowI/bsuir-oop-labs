#include "Canvas.h"
#include "../Figures/Ellipse.h"
#include "../Figures/Rect.h"
#include "../Figures/Triangle.h"


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

    m_figures[index]->Move(x, y);
}
void Canvas::FillFigure(int index, char f) {
    if (index == -1) return;

    m_figures[index]->SetFillChar(f);
}

void Canvas::Save(std::string path){
    if (m_figures.empty()) return;

    std::ofstream ofs(path + ".lab1");
    if (ofs.is_open()) {
        for (int i = 0; i < m_figures.size(); i++) {
            m_figures[i]->SaveToFile(ofs);
        }
        ofs << '#';
    }
    else {
        std::cout << "Cant open file " << "\n";
    }
    
    ofs.close();
}
void Canvas::Load(std::string path){
    if (!m_figures.empty()) {
        for (int i = 0; i < m_figures.size(); i++) {
            delete m_figures[i];
        }
        m_figures.clear();
    }

    std::ifstream ifs(path);
    if (ifs.is_open()) {
        while (true) {
            char type;
            ifs.read(&type, 1);
            if (type == '#') break;

            char* figure;
            switch (type) {
            case 'e':
                figure = new char[sizeof(Elipse)];
                ifs.read(figure, sizeof(Elipse));
                m_figures.push_back((IFigure*)figure);
                break;
            case 'r':
                figure = new char[sizeof(Rect)];
                ifs.read(figure, sizeof(Rect));
                m_figures.push_back((IFigure*)figure);
                break;
            case 't':
                figure = new char[sizeof(Triangle)];
                ifs.read(figure, sizeof(Triangle));
                m_figures.push_back((IFigure*)figure);
                break;
            }
        }
       
    }

    ifs.close();
}