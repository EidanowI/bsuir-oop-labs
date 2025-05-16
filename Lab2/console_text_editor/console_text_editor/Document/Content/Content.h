#pragma once
#include <vector>
#include <iostream>
#include <Windows.h>
#include "../HistoryManager.h"
#include "Decorator/Decorator.h"



struct Highlight {
	int begin = 0;
	int end = 0;

	void Clear() {
		begin = 0;
		end = 0;
	}
};

class Content {
	friend class LocalSaver;
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
	void Paste();

	void Print();
private:

	void MoveCursorLeft();
	void MoveCursorRight();

	void MoveHLLeft();
	void MoveHLRight();

	void CopyToClipboard();

private:
	bool m_isEditable = false;

	std::vector<char> m_data;
	int cursor_pos = 0;

	HestoryManager m_history_manager;

	Highlight m_textSelection_highlight;
public:
	IFormator* m_pFormator;
};