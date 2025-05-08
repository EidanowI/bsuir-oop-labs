#pragma once
#include <vector>
#include <iostream>



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

private:
	void Print();

private:
	bool m_isEditable;

	std::vector<char> m_data;
	int cursor_pos = 0;
};