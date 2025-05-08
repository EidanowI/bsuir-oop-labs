#pragma once
#include <vector>
#include <iostream>
#include "../HistoryManager.h"



class Content {
public:
	Content(bool isEditable);
	Content(bool isEditable, std::vector<char> data);
	~Content();

	/*Thats shit will return true if the content was changed so we need to record date*/
	bool Edit();

	void SetIsEditable(bool isEditable) {
		m_isEditable = isEditable;
	}

	std::vector<char>& GetData() {
		return m_data;
	}

	void AddChar(char ch);
	void DeleteChar();

private:
	void Print();

	void MoveCursorLeft();
	void MoveCursorRight();

private:
	bool m_isEditable = false;

	std::vector<char> m_data;
	int cursor_pos = 0;

	HestoryManager m_history_manager;
};