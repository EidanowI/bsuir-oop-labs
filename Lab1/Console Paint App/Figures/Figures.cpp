#include "../Canvas/Canvas.h"
#include "IFigure.h"
#include "Ellipse.h"



Elipse::Elipse(int x, int y, int a, int b, char f){
	m_name = "Ellipse #" + (char)('a' + rand() % 'x') + (char)('a' + rand() % 'x');
	m_x = x;
	m_y = y;
	m_a = a;
	m_b = b;
	m_fillChar = f;
}
Elipse::~Elipse(){

}

void Elipse::AddToCanvas(char* canvas) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			//if ((abs(j-x) < a && abs(i-y) < b)){
			//	((Canvas*)canvas)->GetScreenBuffer()[i * WIDTH + j] = '#';
			//}

			if ((float)((j - m_x) * (j - m_x)) / (m_a * m_a) + (float)((i - m_y) * (i - m_y)) / (m_b * m_b) <= 1) {
				((Canvas*)canvas)->GetScreenBuffer()[i * WIDTH + j] = m_fillChar;
			}
		}
	}
}

int Elipse::GetSquare() {
	int square = 0;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if ((float)((j - m_x) * (j - m_x)) / (m_a * m_a) + (float)((i - m_y) * (i - m_y)) / (m_b * m_b) <= 1) {
				square++;
			}
		}
	}
	return square;
}