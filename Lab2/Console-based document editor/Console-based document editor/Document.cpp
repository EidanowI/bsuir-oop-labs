#include "Document.h"


static bool aa = true;



void Document::Edit() {
	aa = true;

	std::cout << "Aditing is allowed for: " << "\n";
	std::cout << "Manage permissions." << "\n";
	std::cout << "Export to local machine." << "\n";
	std::cout << "Export to cloud." << "\n";


	while (true) {
		bool is_shift = false;
		is_shift = GetAsyncKeyState(16) < 0;
		bool is_ctrl = false;
		is_ctrl = GetAsyncKeyState(17) < 0;
		bool is_alt = false;
		is_ctrl = GetAsyncKeyState(18) < 0;

		for (int key = 0; key < 256; key++) {
			if (GetAsyncKeyState(key) & 0x8000){
				//std::cout << key << "  ";
				if (key == 37) {
					if (is_shift) {

					}
					else {
						std::cout << '\b';
					}
				}
				if (key == 39) {
					if (is_shift) {

					}
					else {
						std::cout << "\033[C";
					}
				}

				if (key == 8) {
					std::cout << '\b' << ' ' << '\b';
				}

				if (key == 9) std::cout << "  ";

				if (key == 32) std::cout << ' ';

				if (key == 192) std::cout << (is_shift ? '~' : '`');

				if (key == 49) std::cout << (is_shift ? '!' : '1');
				if (key == 50) std::cout << (is_shift ? '@' : '2');
				if (key == 51) std::cout << (is_shift ? '#' : '3');
				if (key == 52) std::cout << (is_shift ? '$' : '4');
				if (key == 53) std::cout << (is_shift ? '%' : '5');
				if (key == 54) std::cout << (is_shift ? '^' : '6');
				if (key == 55) std::cout << (is_shift ? '&' : '7');
				if (key == 56) std::cout << (is_shift ? '*' : '8');
				if (key == 57) std::cout << (is_shift ? '(' : '9');

				if (key == 48) std::cout << (is_shift ? ')' : '0');

				if (key == 189) std::cout << (is_shift ? '_' : '-');

				if (key == 187) std::cout << (is_shift ? '+' : '=');
				if (key == 191) std::cout << (is_shift ? '?' : '/');
				if (key == 190) std::cout << (is_shift ? '>' : '.');
				if (key == 188) std::cout << (is_shift ? '<' : ',');

				if (key == 220) std::cout << (is_shift ? '|' : '\\');
				if (key == 219) std::cout << (is_shift ? '{' : '[');
				if (key == 221) std::cout << (is_shift ? '}' : ']');
				if (key == 186) std::cout << (is_shift ? ':' : ';');
				if (key == 222) std::cout << (is_shift ? '"' : '\'');


				if (key >= 'A' && key <= 'Z') {
					if (!is_shift) {
						std::cout << (char)(key + 'a' - 'A');
					}
					else {
						std::cout << (char)key;
					}
				}
			}
		}
		Sleep(100);
	}

}