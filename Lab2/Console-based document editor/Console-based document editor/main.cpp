#include <iostream>
#include "Auth/User.h"
#include "Document.h"


bool G_is_editor_rinning = true;



int main() {
	UserManager::Init();

	//Document dd{};
	//dd.Edit();

	while (G_is_editor_rinning) {
		system("CLS");

		while (true) {
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

					if (UserManager::TryFindUser(login)) {
						std::cout << "User already axist!\n";
					}
					else {
						std::cout << "Password: ";
						std::string password;
						std::cin >> password;

						UserManager::Register(login, password);

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

					if (UserManager::TryFindUser(login)) {
						while (true) {
							std::cout << "Password: ";
							std::string password;
							std::cin >> password;

							if (UserManager::Login(login, password)) {
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


		while (UserManager::GetCurrentUser()) {
			system("CLS");
			std::cout << "You loged as \033[32m" << UserManager::GetCurrentUser()->GetLogin() << "\033[0m\n";

			std::cout << "1. - logout;\n";
			std::cout << "2. - open document;\n";

			char in;
			std::cin >> in;

			if (in == '1') {
				UserManager::Logout();
				break;
			}
			else if (in == '2') {
				std::cout << "Doc name: ";
				std::string name;
				std::cin >> name;
				Document document(UserManager::GetCurrentUser(), name);

				document.PrintMenu();
			}
		}
	}

	UserManager::Term();

	return 0;
}