#pragma once
#include <iostream>
#include "Command/ICommand.h"


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
	Line(){}
	Line(char* data);

	void Print();

	void SetLineNumber(int line_number);

	void AddChar(char ch, int x) {
		if (m_data[139]) return;

		for (int i = 139; i >= x; i--) {
			m_data[i] = m_data[i - 1];
		}

		m_data[x] = ch;

		Print();
	}

	void DelChar(int x) {
		for (int i = x; i < 138; i++) {
			m_data[i] = m_data[i + 1];
		}

		Print();
	}

public:
	int m_line_number;

	char m_data[140]{};
};


class HistoryCommand {
public:
	HistoryCommand() {
		top = -1;
	}

	void AddCommand(ICommand* command) {
		/*while (m_commands.size() - 1 != top && !m_commands.empty()) {
			m_commands.pop_back();
		}*/

		m_commands.push_back(command);
		top = m_commands.size()-1;
	}

	ICommand* GetCommand() {
		auto ret = m_commands[top];

		if (top != 0) {
			top--;
		}
		return ret;
	}

private:
	int top = 0;
	std::vector<ICommand*> m_commands;
};

class Content {
public:
	Content(bool is_editable);
	~Content();

	bool Edit();///return true if user change content

	void ReprintAllLines();

	void SetCarrige(Vec2 pos);
	void SetCarrigeToOrigin();

	bool IsInserMode();

	void AddLine(Line line);

	void MoveCursorLeft() {
		//ClearHighlg();

		if (m_carriage_pos.x > 0) {
			m_carriage_pos.x--;
		}
		SetCarrigeToOrigin();
	}
	void MoveCursorRight() {
		//ClearHighlg();

		if (m_carriage_pos.x < 139) {
			m_carriage_pos.x++;
		}
		SetCarrigeToOrigin();
	}

private:
	bool m_editable;

	bool m_isInsert_mode;

	std::vector<Line> m_lines;

	Vec2 m_carriage_pos;

	HistoryCommand m_history_commands;
};