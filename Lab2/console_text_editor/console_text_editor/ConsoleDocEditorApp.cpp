#include <filesystem>

#include "ConsoleDocEditorApp.h"
#include "User/LocalStorageUserRepo.h"
#include "User/User.h"
#include "File/FileDialog.h"



bool G_is_editor_rinning = true;


ConsoleDocEditorApp::ConsoleDocEditorApp() {
	m_pUser_repo = new LocalStorageUserRepo();
}
ConsoleDocEditorApp::~ConsoleDocEditorApp() {
	if(m_pUser_repo) delete m_pUser_repo;
}

void ConsoleDocEditorApp::Run() {
	m_pUser_repo->LoadRegUsers();

	while (G_is_editor_rinning) {
		system("CLS");

		while (true) {///Reg-Log menu
			std::cout << "Q - Quit;\n";
			std::cout << "R - Register;\n";
			std::cout << "L - Login;\n";

			std::cout << ":";
			char in;
			std::cin >> in;

			if (in == 'Q' || in == 'q') {
				G_is_editor_rinning = false;
				break;
			}
			else if (in == 'R' || in == 'r') {
				while (true) {
					std::cout << "Login: ";
					std::string login;
					std::cin >> login;

					if (m_pUser_repo->GetUser(login)) {
						std::cout << "User already axist!\n";
					}
					else {
						std::cout << "Password: ";
						std::string password;
						std::cin >> password;

						m_pUser_repo->AddNewUser(login, password);

						break;
					}
				}
				break;
			}
			if (in == 'L' || in == 'l') {
				while (true) {
					std::cout << "Login: ";
					std::string login;
					std::cin >> login;

					auto pUser = m_pUser_repo->GetUser(login);
					if (pUser) {
						while (true) {
							std::cout << "Password: ";
							std::string password;
							std::cin >> password;

							if (pUser->TryToLogin(password)) {
								m_pUser = pUser;
								break;
							}
							else {
								std::cout << "Incorrect password!\n";
							}
						}
						break;
					}
					else {
						std::cout << "User not axist!\n";
					}
				}
				break;
			}
			std::cout << "Invalid command! Use given comands.\n";
		}

		if (!m_pUser) continue;

		system("CLS");

		while (true) {///Open new or exist document
			std::cout << "You " << "\033[33m" << ((User*)m_pUser)->GetLogin() << "\033[0m\n";
			std::cout << "1. - New document\n";
			std::cout << "2. - Open document\n";

			char in;
			std::cin >> in;

			if (in == '1') {
				m_pDocument = new Document((LocalStorageUserRepo*)m_pUser_repo, (User*)m_pUser);

				break;///give user inside new doc() and new doc().isEditable();
			}
			else if (in == '2') {
				std::string name;
				std::cout << "Write file name without extension: ";
				std::cin >> name;

				std::string path = name;

				m_pDocument = new Document((LocalStorageUserRepo*)m_pUser_repo, (User*)m_pUser, path);

				break;
			}
			else {
				std::cout << "Incorrect command!\n";
			}
		}

		while (true) {
			std::cout << "You are " << "\033[33m" << ((User*)m_pUser)->GetLogin() << "\033[0m";
			if (m_pDocument->GetIsEditable()) std::cout << "(editor)\n";
			else std::cout << "(viewer-only)\n";

			std::cout << "Q. - To menu\n";
			if(m_pUser->IsAdmin()) std::cout << "C. - Change permissions\n";
			std::cout << "L. - To show editors and their dates\n";
			//std::cout << "I. - Import from file\n";
			std::cout << "S. - Saving .lab2 document\n";
			std::cout << "E. - Export to file\n";
			std::cout << "D - Edit document\n";	


			char in;
			std::cin >> in;

			if (in == 'Q') {
				m_pUser = nullptr;
				break;
			}
			else if (in == 'C' && m_pUser->IsAdmin()) {///change permissions
				system("CLS");
				m_pDocument->PrintAllUsers((LocalStorageUserRepo*)m_pUser_repo);
				std::string in_login;
				std::cin >> in_login;

				auto a = m_pUser_repo->GetUser(in_login);
				if (a) {
					m_pDocument->ChangePermissionForUser((LocalStorageUserRepo*)m_pUser_repo, (User*)a);
				}
			}
			else if (in == 'L') {
				system("CLS");
				m_pDocument->PrintAllUsers((LocalStorageUserRepo*)m_pUser_repo);
			}
			//else if (in == 'I') {///import from file
			//	m_pDocument->ImportFromFile();
			//}
			else if (in == 'S') {///saving .lab2 document
				ISaverStrategy* saver_strategy = nullptr;

				std::string file_name;
				std::cout << "Enter file name without extension: ";
				std::cin >> file_name;

				while (true) {
					std::cout << "1. - No options\n";
					std::cout << "2. Save with cloud\n";

					char in;
					std::cin >> in;

					if (in == '1') {
						break;
					}
					else if (in == '2') {
						saver_strategy = new CloudStrategy();
						break;
					}
					else {
						std::cout << "Incorect command!\n";
					}
				}

				m_pDocument->SaveDocument(file_name, saver_strategy);

				delete saver_strategy;
			}
			else if (in == 'E') {///export to file
				m_pDocument->ExportToFile();
			}
			else if (in == 'D') {///edit document
				m_pDocument->Edit((User*)m_pUser);
			}
			else {
				std::cout << "Incorrect input!\n";
			}
		}

		delete m_pDocument;
		m_pDocument = nullptr;
		/*while (m_pDocument) {///Loged menu		
			
			std::cout << "1. - Logout\n";
			std::cout << "2. - Change user permissions\n";
			std::cout << "3. - Open document\n";
			
			char in;
			std::cin >> in;

			if (in == '1') {
				m_pUser = nullptr;

				break;
			}
			else if (in == '2') {
				if (m_pUser != m_pUser_repo->GetUser("admin")) {
					std::cout << "\033[31mThis user cant change permissions!\033[0m\n";
					continue;
				}

				while (true) {
					system("CLS");

					std::cout << "Q - to quit\n";
					m_pUser_repo->LogAllUsers();

					std::string inp;
					std::cin >> inp;

					auto size = inp.size();
					if (inp.size() == 1 && (inp[0] == 'Q' || inp[0] == 'q')) {
						system("CLS");
						break;
					}
					auto a = m_pUser_repo->GetUser(inp);
					if (a != nullptr) {
						system("CLS");
						m_pUser->ChangePermission(a);
					}
				}
			}
			else if (in == '3') {
				std::cout << "Document name: ";
				std::string file_name;
				std::cin >> file_name;

				m_pUser->OpenDocumentContext("Docs/" + file_name, ((User*)m_pUser)->GetLogin());

				//system("CLS");//needed here for beauty
			}
			else {
				std::cout << "Incorrect command!\n";
			}
		}*/
	}
}