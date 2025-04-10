#pragma once
#include <chrono>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <ctime>



extern bool G_is_editor_rinning;

class Line {
	friend class Document;
public:
	Line(int line_number) {
		m_line_number = line_number;
	}

	void Print() {
		std::cout << "\033[" + std::to_string(m_line_number + 1) + ";1H";

		for (int i = 0; i < 139; i++) {
			if (m_data[i] == 0) {
				std::cout << ' ';
			}
			std::cout << m_data[i];
		}
	}

	void AddChar(char ch, int x) {
		if (m_data[139]) return;

		for (int i = 139; i >= x; i--) {
			m_data[i] = m_data[i - 1];
		}
		/*if (m_data[139]) return;

		for (int i = x-1; i < 139; i++) {
			m_data[i + 1] = m_data[i];
		}*/
		m_data[x] = ch;

		Print();
	}
	void InsertChar(char ch, int x) {
		m_data[x] = ch;

		Print();
	}

private:
	int m_line_number;

	char m_data[140]{};
};

class Document {
public:
	Document() {
		m_lines.push_back(Line(0));
	}

	void MoveCursorLeft() {
		if (m_cursor_pos_x > 0) {
			m_cursor_pos_x--;
		}
		SetCarriage();
	}
	void MoveCursorRight() {
		if (m_cursor_pos_x < 139) {
			m_cursor_pos_x++;
		}
		SetCarriage();
	}

	

	void AddChar(bool is_insert_mode, char ch) {
		if (is_insert_mode) {
			m_lines[m_cursor_pos_y].InsertChar(ch, m_cursor_pos_x);
			m_cursor_pos_x++;
			SetCarriage();
		}	
		else {
			if (!m_lines[m_cursor_pos_y].m_data[138]) {
				m_lines[m_cursor_pos_y].AddChar(ch, m_cursor_pos_x);
				m_cursor_pos_x++;
				SetCarriage();
			}		
		}
	}

	void Edit();

private:
	void SetCarriage() {
		std::cout << "\033[" + std::to_string(m_cursor_pos_y + 1) + ";" + std::to_string(m_cursor_pos_x + 1) + "H";
	}

private:
	int m_cursor_pos_x = 0;
	int m_cursor_pos_y = 0;

	std::vector<Line> m_lines;
};