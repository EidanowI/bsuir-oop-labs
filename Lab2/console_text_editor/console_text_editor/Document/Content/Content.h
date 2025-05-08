#pragma once
#include <vector>
#include <iostream>
#include <Windows.h>
#include "../HistoryManager.h"



struct Highlight {
	int begin = 0;
	int end = 0;

	void Clear() {
		begin = 0;
		end = 0;
	}
};

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
	void Paste();

private:
	void Print();

	void MoveCursorLeft();
	void MoveCursorRight();

	void MoveHLLeft() {
		if (cursor_pos > 0) {
			cursor_pos--;
		}

		if (m_textSelection_highlight.end == 0) {
			m_textSelection_highlight.end = cursor_pos + 1;
		}
		m_textSelection_highlight.begin = cursor_pos;

		Print();
	}
	void MoveHLRight() {
		if (cursor_pos < m_data.size()) {
			cursor_pos++;
		}

		if (m_textSelection_highlight.begin == 0) {
			m_textSelection_highlight.begin = cursor_pos - 1;
		}
		m_textSelection_highlight.end = cursor_pos;

		Print();
	}

	void CopyToClipboard() {
		if (OpenClipboard(NULL)) {
			EmptyClipboard();

			std::vector<char> bb;
			int i = m_textSelection_highlight.begin;
			while (i != m_textSelection_highlight.end) {
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
	bool m_isEditable = false;

	std::vector<char> m_data;
	int cursor_pos = 0;

	HestoryManager m_history_manager;

	Highlight m_textSelection_highlight;
};