#include "Line.h"



Line::Line(int line_number) {
	m_line_number = line_number;

	ClearHighlight();

	m_data[0] = 'A';
	m_data[139] = 'B';
}

void Line::Print() {
	std::cout << "\033[" + std::to_string(m_line_number + 1) + ";1H";

	for (int i = 0; i < 140; i++) {
		if (m_highlight_begin != m_highlight_end) {
			if (m_highlight_begin == i) {
				std::cout << "\033[3;100;30m";
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

void Line::AddChar(char ch, int x) {
	if (m_data[139]) return;

	for (int i = 139; i >= x; i--) {
		m_data[i] = m_data[i - 1];
	}

	m_data[x] = ch;

	Print();
}
void Line::InsertChar(char ch, int x) {
	m_data[x - 1] = ch;

	Print();
}
void Line::DelChar(int x) {
	for (int i = x; i < 138; i++) {
		m_data[i] = m_data[i + 1];
	}

	Print();
}

void Line::ClearHighlight() {
	m_highlight_begin = 0;
	m_highlight_end = 0;
}
void Line::Copy() {
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