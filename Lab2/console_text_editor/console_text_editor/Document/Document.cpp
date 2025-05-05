#include <iostream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <Windows.h>

#include "EditPermissionOpener.h"
#include "ViewPermissionOpener.h"
#include "Document.h"

#include "Import/TXTImporterAdapter.h"
#include "Command/AddCharCommand.h"
#include "Command/DeleteCommand.h"



EditPermissionOpener::EditPermissionOpener() {

}
EditPermissionOpener::~EditPermissionOpener() {

}

void EditPermissionOpener::OpenDocumentContext(std::string path, char* opener) {
	Document* edit_document = new Document(true, opener);

	edit_document->Open(path);

	while (true) {
		std::cout << path << "\033[32m (Editable)\033[0m\n";
		std::cout << "1. - Edit\n";
		std::cout << "2. - Save\n";
		std::cout << "3. - Quit\n";

		char in;
		std::cin >> in;

		if (in == '1') {
			edit_document->Edit();
		}
		else if (in == '2') {
			edit_document->Save();
		}
		else if (in == '3') {
			break;
		}
		else {
			std::cout << "Invalid value!";
		}
	}

	delete edit_document;
}


ViewPermissionOpener::ViewPermissionOpener() {

}
ViewPermissionOpener::~ViewPermissionOpener() {

}

void ViewPermissionOpener::OpenDocumentContext(std::string path, char* opener) {
	if (std::filesystem::exists(path)) {
		Document* view_document = new Document(false, opener);

		view_document->Open(path);

		while (true) {
			std::cout << path << "\033[31m (View-only)\033[0m\n";
			std::cout << "1. - Edit\n";
			std::cout << "2. - Save\n";
			std::cout << "3. - Quit\n";

			char in;
			std::cin >> in;

			if (in == '1') {
				view_document->Edit();
			}
			else if (in == '2') {
				view_document->Save();
			}
			else if (in == '3') {
				break;
			}
			else {
				std::cout << "Invalid value!";
			}
		}

		delete view_document;
	}
	else {
		std::cout << "\033[31m" << "File does not exist. So viewer cant creates files." << "\033[0m\n";
	}
}


Document::Document(bool is_editable, char* opener) : m_isEditable(is_editable), m_opener(opener), m_content(m_isEditable){
	//m_isDocument_content_changed = false;
}
Document::~Document() {

}

void Document::Open(std::string name) {
	if (std::filesystem::exists(name)) {
		std::vector<Line> imported_lines;

		if (name[name.size() - 1] == 't') {
			auto pImporter = new TXTImporterAdapter();
			imported_lines = pImporter->Import(m_author, m_edit_date, name);
		}

		for (int i = 0; i < imported_lines.size(); i++) {
			m_content.AddLine(imported_lines[i]);
		}
	}
	else {
		char a[] = "Hello wordls!";
		m_content.AddLine(Line(a));
	}
}
void Document::Save() {
	std::cout << "SAVE";
}
void Document::Edit() {
	bool is_should = m_content.Edit();

	if (is_should) {
		m_author = m_opener;

		auto a = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::tm* now_tm = std::localtime(&a);

		std::ostringstream oss;
		oss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");

		m_edit_date = oss.str();
	}
}

std::string& Document::GetAuthor() {
	return m_opener;
}
std::string& Document::GetEditDate() {
	return m_edit_date;
}


Content::Content(bool is_editable) : m_editable(is_editable) {
	m_isInsert_mode = false;

	m_carriage_pos = Vec2(0, 0);
}
Content::~Content() {

}

bool Content::Edit() {///return true if user change content
	system("CLS");

	ReprintAllLines();

	while (true) {
		Sleep(100);

		bool is_shift = false;
		is_shift = GetAsyncKeyState(16) < 0;
		bool is_ctrl = false;
		is_ctrl = GetAsyncKeyState(17) < 0;
		bool is_alt = false;
		is_alt = GetAsyncKeyState(18) < 0;
		
		for (int key = 0; key < 256; key++) {
			if (GetAsyncKeyState(key) & 0x8000){
				if (key == 37) {
					if (is_shift) {
						//HighlightLeft();
					}
					else {
						MoveCursorLeft();
					}
				}
				if (key == 39) {
					if (is_shift) {
						//HighlightRight();
					}
					else {
						MoveCursorRight();
					}
				}

				if (key == 27) {
					return true;
				}

				if (key == 8) {
					if (m_editable) {
						auto command = new DeleteCommand(m_lines);///state here
						m_history_commands.AddCommand(command);
						command->Delete(m_lines[m_carriage_pos.y], m_carriage_pos.x);
						MoveCursorLeft();
						SetCarrigeToOrigin();
					}
				}

				if (key == 13) {
					if (m_lines.size() - 1 == m_carriage_pos.y) {
						char c[] = "";
						auto line = Line(c);
						line.SetLineNumber(m_lines.size());
						m_lines.push_back(line);
					}

					m_carriage_pos.y++;

					m_carriage_pos.x = 0;
					for (int i = 139; i != 0; i--) {
						if (m_lines[m_carriage_pos.y].m_data[i] != 0) {
							m_carriage_pos.x = i+1;
						}
					}

					SetCarrigeToOrigin();
				}

				if (key == 38) {
					if (m_carriage_pos.y != 0) {
						m_carriage_pos.y--;
					}
					SetCarrigeToOrigin();
					//MoveCursorUp();
				}
				if (key == 40) {
					//MoveCursorDown();
				}

		/*		if (key == 32) AddChar(' ');

				if (key == 192) AddChar((is_shift ? '~' : '`'));

				if (key == 49) AddChar((is_shift ? '!' : '1'));
				if (key == 50) AddChar((is_shift ? '@' : '2'));
				if (key == 51) AddChar((is_shift ? '#' : '3'));
				if (key == 52) AddChar((is_shift ? '$' : '4'));
				if (key == 53) AddChar((is_shift ? '%' : '5'));
				if (key == 54) AddChar((is_shift ? '^' : '6'));
				if (key == 55) AddChar((is_shift ? '&' : '7'));
				if (key == 56) AddChar((is_shift ? '*' : '8'));
				if (key == 57) AddChar((is_shift ? '(' : '9'));

				if (key == 48) AddChar((is_shift ? ')' : '0'));

				if (key == 189) AddChar((is_shift ? '_' : '-'));

				if (key == 187) AddChar((is_shift ? '+' : '='));
				if (key == 191) AddChar((is_shift ? '?' : '/'));
				if (key == 190) AddChar((is_shift ? '>' : '.'));
				if (key == 188) AddChar((is_shift ? '<' : ','));

				if (key == 220) AddChar((is_shift ? '|' : '\\'));
				if (key == 219) AddChar((is_shift ? '{' : '['));
				if (key == 221) AddChar((is_shift ? '}' : ']'));
				if (key == 186) AddChar((is_shift ? ':' : ';'));
				if (key == 222) AddChar((is_shift ? '"' : '\''));*/


				if (key >= 'A' && key <= 'Z') {
					if (is_ctrl) {
						if (key == 'I') {
							//SwitchInsert();
						}
						if (key == 'Z') {
							if (is_alt) {
								//REDO();
							}
							else {
								auto a = m_history_commands.GetCommand();
								m_lines = a->BringToState();

								ReprintAllLines();
							}

						}
					}
					else {
						if (m_editable) {
							char ch;
							if (!is_shift) {
								ch = key + 'a' - 'A';
								//AddChar((char)(key + 'a' - 'A'));
							}
							else {
								ch = key;
								//AddChar((char)key);
							}

							auto command = new AddCharCommand(m_lines);///state here
							m_history_commands.AddCommand(command);
							command->AddChar(ch, m_lines[m_carriage_pos.y], m_carriage_pos.x);
							MoveCursorRight();
							SetCarrigeToOrigin();
						}
					}

				}
			}
		}
	}

	return true;
}

void Content::ReprintAllLines() {
	for (int i = 0; i < m_lines.size(); i++) {
		m_lines[i].Print();
	}

	SetCarrige(m_carriage_pos);
}

void Content::SetCarrige(Vec2 pos) {
	std::cout << "\033[" + std::to_string(pos.y + 1) + ";" + std::to_string(pos.x + 1) + "H";
}
void Content::SetCarrigeToOrigin() {
	std::cout << "\033[" + std::to_string(m_carriage_pos.y + 1) + ";" + std::to_string(m_carriage_pos.x + 1) + "H";
}

bool Content::IsInserMode() {
	return m_isInsert_mode;
}

void Content::AddLine(Line line) {
	line.SetLineNumber(m_lines.size());
	m_lines.push_back(line);
}


Line::Line(char* data) {
	for (int i = 0; i < 140; i++) {
		if (data[i]) {
			m_data[i] = data[i];
		}
		else {
			break;
		}
	}
}

void Line::Print() {
	std::cout << "\033[" + std::to_string(m_line_number + 1) + ";1H";

	for (int i = 0; i < 140; i++) {
		/*if (m_highlight_begin != m_highlight_end) {
			if (m_highlight_begin == i) {
				std::cout << "\033[3;100;30m";
			}
			if (m_highlight_end == i) {
				std::cout << "\033[0m";
			}
		}*/
		if (m_data[i] == 0) {
			std::cout << ' ';
		}
		else if (m_data[i] == '\r') {

		}
		else {
			std::cout << m_data[i];
		}
	}
}

void Line::SetLineNumber(int line_number) {
	m_line_number = line_number;
}