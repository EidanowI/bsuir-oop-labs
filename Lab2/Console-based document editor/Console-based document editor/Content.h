#pragma once
#include <chrono>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <ctime>

#include "Auth/User.h"
#include "Line.h"



struct Vec2 {
	Vec2(int x, int y) {
		this->x = x;
		this->y = y;
	}
	Vec2() : Vec2(0, 0) {}
	int x = 0;
	int y = 0;
};

class Content {
public:
	Content(bool isAllowed_editing) {
		m_isAllowed_editing = isAllowed_editing;

		m_isInsert_mode = false;

		m_lines.push_back(Line(0));
		m_lines.push_back(Line(1));

		m_carriage_pos = Vec2(0, 0);
	}
	~Content() {

	}

	void ReprintAllLines() {
		for (int i = 0; i < m_lines.size(); i++) {
			m_lines[i].Print();
		}

		SetCarrige(m_carriage_pos);
	}

	void SetCarrige(Vec2 pos) {
		std::cout << "\033[" + std::to_string(pos.y + 1) + ";" + std::to_string(pos.x + 1) + "H";
	}
	void SetCarrigeToOrigin() {
		std::cout << "\033[" + std::to_string(m_carriage_pos.y + 1) + ";" + std::to_string(m_carriage_pos.x + 1) + "H";
	}

	bool IsInserMode() {
		return m_isInsert_mode;
	}

private:
	bool m_isAllowed_editing;

	bool m_isInsert_mode;

	std::vector<Line> m_lines;

	Vec2 m_carriage_pos;
};