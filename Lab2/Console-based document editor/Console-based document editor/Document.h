#pragma once
#include <chrono>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <ctime>

#include "Auth/User.h"



extern bool G_is_editor_rinning;

class Line {
	friend class Document;
public:
	Line(int line_number) {
		m_line_number = line_number;

		ClearHighlight();
	}

	void Print() {
		std::cout << "\033[" + std::to_string(m_line_number + 1) + ";1H";

		for (int i = 0; i < 139; i++) {
			if (m_highlight_begin != m_highlight_end) {
				if (m_highlight_begin == i) {
					std::cout << "\033[3;100;30m";// Texting\033[0m
				}
				if (m_highlight_end == i) {
					std::cout << "\033[0m";
				}
			}
			if (m_data[i] == 0) {
				std::cout << ' ';
			}
			else {
				std::cout << m_data[i];
			}			
		}
	}

	void DelChar(int x) {
		for (int i = x; i < 138; i++) {
			m_data[i] = m_data[i + 1];
		}

		Print();
	}
	void AddChar(char ch, int x) {
		if (m_data[139]) return;

		for (int i = 139; i >= x; i--) {
			m_data[i] = m_data[i - 1];
		}

		m_data[x] = ch;

		Print();
	}
	void InsertChar(char ch, int x) {
		m_data[x - 1] = ch;

		Print();
	}

	void ClearHighlight() {
		m_highlight_begin = 0;
		m_highlight_end = 0;
	}

	void Copy() {
		if (OpenClipboard(NULL)) {
			EmptyClipboard(); 

			std::vector<char> bb;
			int i = m_highlight_begin;
			while (i != m_highlight_end) {
				bb.push_back(m_data[i]);

				i++;
			}
			bb.push_back(0);

			HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, bb.size() + 1);
			if (hGlobal) {
				memcpy(GlobalLock(hGlobal), bb.data(), bb.size() + 1);
				GlobalUnlock(hGlobal);
				SetClipboardData(CF_TEXT, hGlobal);
			}
			CloseClipboard();
		}
	}

private:
	int m_line_number;

	char m_data[140]{};

	///copy past
	int m_highlight_begin = 0;
	int m_highlight_end = 0;
};

class Document {
public:
	Document() {
		m_lines.push_back(Line(0));
	}

	void MoveCursorLeft() {
		ClearHighlg();

		if (m_cursor_pos_x > 0) {
			m_cursor_pos_x--;
		}
		SetCarriage();
	}
	void MoveCursorRight() {
		ClearHighlg();

		if (m_cursor_pos_x < 139) {
			m_cursor_pos_x++;
		}
		SetCarriage();
	}
	void MoveCursorDown() {
		ClearHighlg();

		m_cursor_pos_y++;

		if(m_lines.size()-1 < m_cursor_pos_y){
			m_lines.push_back(Line(m_cursor_pos_y));
		}

		SetCarriage();
	}
	void MoveCursorUp() {
		ClearHighlg();

		if (m_cursor_pos_y == 0) return;

		m_cursor_pos_y--;

		SetCarriage();
	}
	
	void NewLine() {
		ClearHighlg();

		m_cursor_pos_y++;

		m_lines.push_back(Line(0));

		for (int i = m_lines.size() - 1; i > m_cursor_pos_y; i--) {
			m_lines[i] = m_lines[i - 1];
		}

		m_lines[m_cursor_pos_y] = Line(m_cursor_pos_y);

		m_cursor_pos_x = 0;

		for (int i = 0; i < m_lines.size(); i++) {
			m_lines[i].Print();
		}

		SetCarriage();
	}

	void HighlightLeft() {
		if (m_cursor_pos_x > 0) {
			m_cursor_pos_x--;
		}
		SetCarriage();

		if (m_lines[m_cursor_pos_y].m_highlight_end == 0) {
			m_lines[m_cursor_pos_y].m_highlight_end = m_cursor_pos_x + 1;
		}
		m_lines[m_cursor_pos_y].m_highlight_begin = m_cursor_pos_x;

		m_lines[m_cursor_pos_y].Print();
		SetCarriage();
	}
	void HighlightRight() {
		if (m_cursor_pos_x < 139) {
			m_cursor_pos_x++;
		}

		SetCarriage();

		if (m_lines[m_cursor_pos_y].m_highlight_begin == 0) {
			m_lines[m_cursor_pos_y].m_highlight_begin = m_cursor_pos_x - 1;
		}
		m_lines[m_cursor_pos_y].m_highlight_end = m_cursor_pos_x;

		m_lines[m_cursor_pos_y].Print();
		SetCarriage();
	}


	void DelChar() {
		ClearHighlg();

		if (m_is_allowed_editing) {
			if (m_cursor_pos_x > 0) {
				MoveCursorLeft();
				m_lines[m_cursor_pos_y].DelChar(m_cursor_pos_x);
				SetCarriage();
			}	
		}
	}

	void AddChar(char ch) {
		ClearHighlg();

		if (m_is_allowed_editing) {
			UpdateInformation();
			if (m_is_insert) {
				MoveCursorRight();
				m_lines[m_cursor_pos_y].InsertChar(ch, m_cursor_pos_x);
				SetCarriage();
			}
			else {
				if (!m_lines[m_cursor_pos_y].m_data[138]) {
					m_lines[m_cursor_pos_y].AddChar(ch, m_cursor_pos_x);
					MoveCursorRight();
				}
			}
		}		
	}

	void Edit();

	void UpdateInformation() {
		SetCarriage(0, 40);
		char user[]{ "admin" };
		auto now = std::chrono::system_clock::now();
		std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

		std::tm* now_tm = std::localtime(&now_time_t);

		std::cout << "\033[2K";
		std::cout << "\033[32m" << user << (m_is_allowed_editing ? ": " : "(Read-only): ") << "\033[0m" << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S") << (m_is_insert ? " (insert)" : "");//m_current_user->GetLogin();
		SetCarriage();
	}

	void SwitchInsert() {
		ClearHighlg();

		if (!m_is_allowed_editing) return;

		m_is_insert = (m_is_insert ? false : true);

		UpdateInformation();
	}

	void ClearHighlg() {
		for(int i = 0; i < m_lines.size(); i++) {
			m_lines[i].ClearHighlight();
			m_lines[i].Print();
		}
	}

	void CopyToClipboard() {
		m_lines[m_cursor_pos_y].Copy();
	}
	void PastFromClipboard() {

	}

private:
	void SetCarriage() {
		std::cout << "\033[" + std::to_string(m_cursor_pos_y + 1) + ";" + std::to_string(m_cursor_pos_x + 1) + "H";
	}
	void SetCarriage(int x, int y) {
		std::cout << "\033[" + std::to_string(y + 1) + ";" + std::to_string(x + 1) + "H";
	}

private:
	bool m_is_allowed_editing = true;

	User* m_current_user;

	int m_cursor_pos_x = 0;
	int m_cursor_pos_y = 0;

	std::vector<Line> m_lines;

	std::vector<Line> m_undo_lines;


	bool m_is_insert = false;
};