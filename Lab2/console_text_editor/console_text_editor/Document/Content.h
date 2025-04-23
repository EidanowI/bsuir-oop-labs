#pragma once
#include <iostream>



struct Vec2 {
	Vec2(int x, int y) {
		this->x = x;
		this->y = y;
	}
	Vec2() : Vec2(0, 0) {}
	int x = 0;
	int y = 0;
};


class Line {
public:
	Line(char* data) {
		for (int i = 0; i < 140; i++) {
			if (data[i]) {
				m_data[i] = data[i];
			}
			else {
				break;
			}
		}
	}

	void Print() {
		std::cout << "\033[" + std::to_string(m_line_number + 1) + ";1H";

		for (int i = 0; i < 140; i++) {
			/*if (m_highlight_begin != m_highlight_end) {
				if (m_highlight_begin == i) {
					std::cout << "\033[3;100;30m";
				}
				if (m_highlight_end == i) {
					std::cout << "\033[0m";
				}
			}*/
			if (m_data[i] == 0) {
				std::cout << ' ';
			}
			else if (m_data[i] == '\r') {

			}
			else {
				std::cout << m_data[i];
			}
		}
	}

	void SetLineNumber(int line_number) {
		m_line_number = line_number;
	}

private:
	int m_line_number;

	char m_data[140]{};
};


class Content {
public:
	Content(bool is_editable) : m_editable(is_editable){
		m_isInsert_mode = false;

		m_carriage_pos = Vec2(0, 0);
	}
	~Content() {

	}

	bool Edit() {///return true if user change content
		system("CLS");

		ReprintAllLines();

		while (true);

		return true;
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

	void AddLine(Line line) {
		line.SetLineNumber(m_lines.size());
		m_lines.push_back(line);
	}

private:
	bool m_editable;

	bool m_isInsert_mode;

	std::vector<Line> m_lines;

	Vec2 m_carriage_pos;
};