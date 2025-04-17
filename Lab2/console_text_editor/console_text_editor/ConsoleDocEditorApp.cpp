#include "ConsoleDocEditorApp.h"
#include "User/LocalStorageUserRepo.h"



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
		while (true) {///Loged menu
			std::cout << "1. - Logout\n";
			std::cout << "2. - Change user permissions\n";
			
			char in;
			std::cin >> in;

			if (in == '1') {
				m_pUser = nullptr;

				break;
			}
			else if (in == '2') {
				if (m_pUser != m_pUser_repo->GetUser("admin")) {
					std::cout << "This user cant change permissions!\n";
					continue;
				}

				system("CLS");
				while (true) {
					
					std::cout << "Q - to quit\n";
					m_pUser_repo->LogAllUsers();

					std::string inp;
					std::cin >> inp;

					if (inp.size() == 2 || inp[0] == 'Q') {
						break;
					}
					auto a = m_pUser_repo->GetUser(inp);
					m_pUser->ChangePermission(a);
					system("CLS");
				}
			}
			else {
				std::cout << "Incorrect command!\n";
			}
		}
	}
}