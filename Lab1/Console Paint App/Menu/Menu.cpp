#include "Menu.h"



extern bool G_should_quit;


void Menu::DrawMenu() {
	for (int i = 0; i < 68; i++, std::cout << ' ');
	std::cout << "\x1B[32mMENU\033[0m\n";

	switch (m_state)
	{
	case CHOOSING_ACTION:
		std::cout << "Choose action: ";
		std::cout << "\x1B[33mA\033[0m - draw figure; ";
		std::cout << "\x1B[33mD\033[0m - del figure; ";
		std::cout << "\x1B[33mM\033[0m - move figure; ";
		std::cout << "\x1B[33mF\033[0m - fill figure; ";
		std::cout << "\x1B[33mS\033[0m - save; ";
		std::cout << "\x1B[33mL\033[0m - load; ";
		std::cout << "\x1B[33m<\033[0m - undo; ";
		std::cout << "\x1B[33m>\033[0m - redo; ";
		std::cout << "\x1B[31mQ\033[0m - quit; \n";

		DrawOutput();
		
		InputChoosingAction();
		
		break;
	case CHOOSING_OBJECT:
	case MOVE_OBJECT:
	case DELETE_OBJECT:
		///TODO logic to select objects
		std::cout << "logic to select objects ";
		if (m_state == CHOOSING_OBJECT) break;

		if (m_state == MOVE_OBJECT) {
			std::cout << "logic to move objects";
		}
		else {
			std::cout << "logic to delete objects";
		}
		break;
	case INPUT_DRAW_COMMAND:
		std::cout << "Choose figure: ";
		std::cout << "\x1B[33mE x y a b char\033[0m - draw ellipse; ";
		std::cout << "\x1B[33mR x y a b char\033[0m - draw rect; ";
		std::cout << "\x1B[33mT x y a b c char\033[0m - draw triangle; ";
		std::cout << "\x1B[33mQ\033[0m - back; \n";
		std::cout << "\033[3;43;30mREMEMBER you can enter only integers, separated by space\033[0m\n";
		char a;
		std::cin >> a;
		if (a == 'Q') m_state = CHOOSING_ACTION;
		break;
	default:
		break;
	}
}
void Menu::DrawOutput() {
	std::cout << "Output: " << m_output_msg << '\n';
}

void Menu::SetCanvas(Canvas* pCanvas) {
	m_pCanvas = pCanvas;
}

void Menu::InputChoosingAction() {
	char input;
	std::cin >> input;

	switch (input)
	{
	case 'A':
		m_state = INPUT_DRAW_COMMAND;
		break;
	case 'D':
		m_state = DELETE_OBJECT;
		break;
	case 'M':
		m_state = MOVE_OBJECT;
		break;
	case 'S'://Save
		m_pCanvas->Save(FileDialogWindow(L"Save file"));
		break;
	case 'L'://Load
		m_pCanvas->Load(FileDialogWindow(L"Load file"));
		break;
	case 'Q':
		G_should_quit = true;
	default:
		break;
	}
}

LPWSTR Menu::FileDialogWindow(LPCWSTR title) {
	OPENFILENAME ofn;
	wchar_t szFile[260];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFile[0] = '\0';
	ofn.lpstrFilter = L"Lab1 files (*.lab1)\0";
	ofn.lpstrTitle = L"Save File";
	ofn.Flags = OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn)) {
		return ofn.lpstrFile;
	}
	else {
		std::cerr << "\x1B[31mFILE DIALOG FAILED.\033[0m""" << std::endl;
	}
}