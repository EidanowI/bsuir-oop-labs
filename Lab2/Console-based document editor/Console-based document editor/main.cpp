#include <iostream>
#include "Auth/User.h"


bool G_is_editor_rinning = true;
int main() {
	UserManager::Init();

	while (G_is_editor_rinning) {
		system("CLS");

		while (true) {
			std::cout << "Q - Quit;\n";
			std::cout << "R - Register;\n";
			std::cout << "L - Login;\n";

			std::cout << ":";
			char in;
			std::cin >> in;

			if (in == 'Q') {
				G_is_editor_rinning = false;
				break;
			}
			else if (in == 'R') {
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
			if (in == 'L') {
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

			std::cout << "You loged as " << UserManager::GetCurrentUser()->GetLogin() << '\n';

			std::cout << "1. - logout;\n";
			std::cout << "2. - open doc;\n";

			char in;
			std::cin >> in;

			if (in == '1') {
				UserManager::Logout();
				break;
			}
			else if (in == '2') {
				std::cout << "open doc";
			}
		}
		//check if in user show 1.logout - continue
		//2. - open doc
		//need one more llop for open the doc after which again logout-doc menu

		//who and when last time change
	}

	UserManager::Term();

	return 0;
}