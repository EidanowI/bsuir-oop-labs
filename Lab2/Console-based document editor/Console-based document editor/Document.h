#pragma once
#include <chrono>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <ctime>
#include <string>

#include "Auth/User.h"
#include "Line.h"
#include "Content.h"



struct UserInfo {
	UserInfo(User* pUser, long long lastTime_changed) {
		this->pUser = pUser;
		this->lastTime_changed = lastTime_changed;
	}
public:
	User* pUser;
	long long lastTime_changed;
};

class Document {
public:
	Document(User* opener, std::string name);
	~Document();

	void PrintMenu();
	void Edit();

	void ExportAsTxt();
	void ExportAsJson();
	void ExportAsXml();

	void SaveToCloud();

	void PrintDocumentInfo();

	/*
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
		AddUndo();
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
		AddUndo();

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
	void __AddChar(char ch) {
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
	


	void ClearUndoCounter() {
		m_undo_counter = 0;
	}
	void AddUndo() {
		m_undo_counter++;

		if (m_undo_counter >= 5) {
			m_undo_lines.push_back(m_lines[m_cursor_pos_y]);
			m_undo_ind = m_undo_lines.size() - 1;
			ClearRedo();
			ClearUndoCounter();
		}
	}
	void AddUndoEmid() {
		ClearRedo();
		ClearUndoCounter();
		m_undo_lines.push_back(m_lines[m_cursor_pos_y]);
		m_undo_ind = m_undo_lines.size() - 1;
	}
	void UNDO() {
		m_redo_lines.push_back(m_lines[m_undo_lines[m_undo_ind].m_line_number]);

		m_lines[m_undo_lines[m_undo_ind].m_line_number] = m_undo_lines[m_undo_ind];

		m_lines[m_undo_lines[m_undo_ind].m_line_number].Print();

		if (m_undo_ind != 0) {
			m_undo_ind--;
		}

		SetCarriage();
	}
	void REDO() {
		m_lines[m_redo_lines[m_redo_ind].m_line_number] = m_redo_lines[m_redo_ind];

		m_lines[m_redo_lines[m_redo_ind].m_line_number].Print();

		if (m_redo_ind != m_redo_lines.size() - 1) {
			m_redo_ind++;
		}

		SetCarriage();
	}
	void ClearRedo() {
		m_redo_lines.clear();
		m_redo_ind = 0;
	}

private:
	void SetCarriage() {
		std::cout << "\033[" + std::to_string(m_cursor_pos_y + 1) + ";" + std::to_string(m_cursor_pos_x + 1) + "H";
	}*/
	void SetCarriage(int x, int y) {
		std::cout << "\033[" + std::to_string(y + 1) + ";" + std::to_string(x + 1) + "H";
	}

private:
	bool m_is_allowed_editing = false;

	UserInfo* m_openerUser_info;
	std::string m_document_name;

	std::vector<UserInfo> m_editAlowed_users;

	Content m_content;
	/*
	int m_cursor_pos_x = 0;
	int m_cursor_pos_y = 0;

	std::vector<Line> m_lines;

	std::vector<Line> m_undo_lines;
	int m_undo_ind;
	int m_undo_counter = 0;

	std::vector<Line> m_redo_lines;
	int m_redo_ind = 0;


	bool m_is_insert = false;*/
};