#include "../Canvas/Canvas.h"
#include "IFigure.h"
#include "Ellipse.h"
#include "Rect.h"
#include "Triangle.h"



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

Rect::Rect(int x, int y, int a, int b, char f) {
	m_name = "Rect #" + (char)('a' + rand() % 'x') + (char)('a' + rand() % 'x');
	m_x = x;
	m_y = y;
	m_a = a;
	m_b = b;
	m_fillChar = f;
}
Rect::~Rect() {

}

void Rect::AddToCanvas(char* canvas) {
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if(j-m_x >= 0 && j - m_x < m_a && i - m_y >= 0 && i - m_y < m_b){
				((Canvas*)canvas)->GetScreenBuffer()[i * WIDTH + j] = m_fillChar;
			}
		}
	}
}

int Rect::GetSquare() {
	int square = 0;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (j - m_x > 0 && j - m_x <= m_a && i - m_y > 0 && i - m_y <= m_b) {
				square++;
			}
		}
	}
	return square;
}

Triangle::Triangle(int x, int y, int a, int b, char f) {
	m_name = "Rect #" + (char)('a' + rand() % 'x') + (char)('a' + rand() % 'x');
	m_x = x;
	m_y = y;
	m_a = a;
	m_b = b;

	m_fillChar = f;
}
Triangle::~Triangle() {

}

void Triangle::AddToCanvas(char* canvas) {
	float sin_angle = (float)m_b / (float)m_a;


	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (j - m_x >= 0 && j - m_x < m_a) {
				float value = sin_angle * (float)(m_a - j - m_x);

				if (i - m_y >= 0 && i - m_y < m_b) {
					if (i - m_y < m_b - value) {
						((Canvas*)canvas)->GetScreenBuffer()[i * WIDTH + j] = m_fillChar;
					}
				}
			}
		}
	}
}

int Triangle::GetSquare() {
	int square = 0;

	float sin_angle = (float)m_b / (float)m_a;


	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (j - m_x >= 0 && j - m_x < m_a) {
				float value = sin_angle * (float)(m_a - j - m_x);

				if (i - m_y >= 0 && i - m_y < m_b) {
					if (i - m_y < m_b - value) {
						square++;
					}
				}
			}
		}
	}
	return square;
}