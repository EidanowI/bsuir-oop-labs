#include "Document.h"



Document::Document(User* opener, std::string name) : m_content{0} {
	m_document_name = "Docs/" + name + ".lab2";

	m_is_allowed_editing = true;

	UserInfo a = UserInfo(opener, 0);
	m_editAlowed_users.push_back(a);
	m_openerUser_info = &m_editAlowed_users[0];

	m_content = Content(m_is_allowed_editing);

	/*std::ifstream ifs(m_document_name, std::ios::ate | std::ios::binary);
	if (ifs.is_open()) {
		int filse_size = ifs.tellg();

		if (filse_size == 0) {
			m_edit_alowed_users.push_back(m_current_user);
			m_is_allowed_editing = true;
		}
		else {
			ifs.seekg(0);

			int users_count = 0;
			ifs.read((char*)&users_count, 4);

			for (int i = 0; i < users_count; i++) {
				unsigned int user_login_hash;
				ifs.read((char*)&user_login_hash, 4);

				auto pUser = UserManager::GetUserByLoginHash(user_login_hash);

				if (pUser) {
					m_edit_alowed_users.push_back(pUser);

					if (m_current_user->CompareLogin(pUser->GetLogin())) {
						m_is_allowed_editing = true;
					}
				}
			}

			int lines_count = 0;
			ifs.read((char*)&lines_count, 4);

			for (int i = 0; i < lines_count; i++) {
				Line a(0);
				ifs.read((char*)&a, sizeof(Line));

				m_lines.push_back(a);
			}
		}
	}
	else {
		m_edit_alowed_users.push_back(m_current_user);
		m_is_allowed_editing = true;
	}

	ifs.close();

	if (m_current_user->CompareLogin("admin")) {
		m_is_allowed_editing = true;
	}

	if (m_lines.empty())
	{
		m_lines.push_back(Line(0));
	}

	m_content = Content(m_is_allowed_editing);*/
}
Document::~Document() {
	/*std::ofstream ofs(m_document_name, std::ios::binary);

	int users_count = m_edit_alowed_users.size();
	ofs.write((char*)&users_count, 4);

	for (int i = 0; i < users_count; i++) {
		m_edit_alowed_users[i]->WriteToStream(ofs);
	}

	int lines_count = m_lines.size();

	ofs.write((char*)&lines_count, 4);

	for (int i = 0; i < lines_count; i++) {
		ofs.write((char*)&(m_lines[i]), sizeof(Line));
	}

	ofs.close();*/
}

void Document::PrintMenu() {
	while (true) {
		system("CLS");
		std::cout << m_document_name << '\n';
		std::cout << "You are \033[32m" << m_openerUser_info->pUser->GetLogin() << "\033[0m\n";
		std::cout << "Aditing is allowed for:\n";
		for (int i = 0; i < m_editAlowed_users.size(); i++) {
			std::tm* now_tm = std::localtime(&m_editAlowed_users[i].lastTime_changed);

			std::cout << "\033[33m" << m_editAlowed_users[i].pUser->GetLogin() << "\033[0m";
			if (m_editAlowed_users[i].lastTime_changed == 0) {
				std::cout << "(newer open this doc)";
			}
			else {
				std::cout << "(" << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S") << ")";
			}	

			std::cout << '\n';
		}

		std::cout << "1. - Export to local machine." << "\n";
		std::cout << "2. - Save to cloud." << "\n";
		std::cout << "3. - " << (m_is_allowed_editing ? "Edit." : "View.") << "\n";
		std::cout << "4. - Quit and save." << "\n";

		if (m_openerUser_info->pUser->IsAdmin()) {
			std::cout << "5. - Manage permisions." << "\n";
		}

		while (true) {
			char in;
			std::cin >> in;

			if (in == '1') {//Export to local
				system("CLS");
				std::cout << "Export to local machine as:\n";
				std::cout << "1. - .txt\n";
				std::cout << "2. - .json\n";
				std::cout << "3. - .xml\n";
				std::cout << "4. - Quit";

				char in_e;
				std::cin >> in_e;
				while (true) {
					if (in_e == '1') {
						ExportAsTxt();
						break;
					}
					if (in_e == '2') {
						ExportAsJson();
						break;
					}
					if (in_e == '3') {
						ExportAsXml();
						break;
					}
					if (in_e == '4') {
						break;
					}
				}
				break;
			}
			if (in == '2') {//Save to cloud
				break;
			}
			if (in == '3') {//Edit
				Edit();
				break;
			}
			if (in == '4') {//Quit
				return;
				break;
			}
			if (in == '5') {//Admin panel
				if (m_openerUser_info->pUser->IsAdmin()) {
					
				}
			}
		}
	}
}

void Document::Edit() {
	system("CLS");
	PrintDocumentInfo();

	m_content.ReprintAllLines();

	while (true) {
		Sleep(100);

		bool is_shift = false;
		is_shift = GetAsyncKeyState(16) < 0;
		bool is_ctrl = false;
		is_ctrl = GetAsyncKeyState(17) < 0;
		bool is_alt = false;
		is_alt = GetAsyncKeyState(18) < 0;
		/*
		for (int key = 0; key < 256; key++) {
			if (GetAsyncKeyState(key) & 0x8000){
				if (key == 37) {
					if (is_shift) {
						HighlightLeft();
					}
					else {
						MoveCursorLeft();
					}
				}
				if (key == 39) {
					if (is_shift) {
						HighlightRight();
					}
					else {
						MoveCursorRight();
					}
				}

				if (key == 27) {
					return;
				}

				if (key == 8) {
					DelChar();
				}

				if (key == 13) {
					NewLine();
				}

				if (key == 38) {
					MoveCursorUp();
				}
				if (key == 40) {
					MoveCursorDown();
				}

				if (key == 9) {
					AddChar(' ');
					AddChar(' ');
					AddChar(' ');
				}			

				if (key == 32) AddChar(' ');

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
				if (key == 222) AddChar((is_shift ? '"' : '\''));


				if (key >= 'A' && key <= 'Z') {
					if (is_ctrl) {
						if (key == 'I') {
							SwitchInsert();
						}
						if (key == 'P') {
							CopyToClipboard();
						}
						if (key == 'V') {
							AddUndoEmid();

							HANDLE clip = 0;

							if (OpenClipboard(NULL)) {
								clip = GetClipboardData(CF_TEXT);
								CloseClipboard();
							}


							//string text;
							//text = (char*)clip;
							char* a = (char*)clip;
								if (a) {
									while (*a) {
										__AddChar(*a);
										a++;
									}
								}
								
						}
						if (key == 'Z') {
							if (is_alt) {
								REDO();
							}
							else {
								UNDO();
							}
							
						}
					}
					else {
						
						if (!is_shift) {
							AddChar((char)(key + 'a' - 'A'));
						}
						else {
							AddChar((char)key);
						}
					}
					
				}
			}
		}
		*/
	}

}

void Document::ExportAsTxt() {}
void Document::ExportAsJson() {}
void Document::ExportAsXml() {}

void Document::SaveToCloud() {}

void Document::PrintDocumentInfo() {
	m_openerUser_info->lastTime_changed = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	
	SetCarriage(0, 40);

	std::tm* now_tm = std::localtime(&m_openerUser_info->lastTime_changed);

	std::cout << "\033[2K";
	std::cout << "\033[32m" << m_openerUser_info->pUser->GetLogin() << (m_is_allowed_editing ? ": " : "(Read-only): ") << "\033[0m" << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S") << (m_content.IsInserMode() ? " (insert)" : "");//m_current_user->GetLogin();

	m_content.SetCarrigeToOrigin();
}