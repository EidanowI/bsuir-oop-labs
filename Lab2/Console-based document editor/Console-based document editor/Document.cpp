#include "Document.h"



void Document::Edit() {
	UpdateInformation();

	//std::cout << "Aditing is allowed for: " << "\n";
	//std::cout << "Manage permissions." << "\n";
	//std::cout << "Export to local machine." << "\n";
	//std::cout << "Export to cloud." << "\n";


	while (true) {
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
				//std::cout << key << " ";
				/*if (key == 13) {
					std::cout << '\n';
				}

				if (key == 37) {
					if (is_shift) {

					}
					else {
						std::cout << "\033[D";
					}
				}
				if (key == 38) {
					std::cout << "\033[A";
				}
				if (key == 40) {
					std::cout << "\033[B";
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
				}*/

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
										AddChar(*a);
										a++;
									}
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
		Sleep(100);
	}

}