#pragma once
#include <chrono>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <ctime>

#include "Auth/User.h"



class Line {
	friend class Document;
public:
	Line(int line_number);

	void Print();

	void AddChar(char ch, int x);
	void InsertChar(char ch, int x);
	void DelChar(int x);
	

	void ClearHighlight();

	void Copy();

private:
	int m_line_number;

	char m_data[140]{};

	///copy past
	int m_highlight_begin = 0;
	int m_highlight_end = 0;
};