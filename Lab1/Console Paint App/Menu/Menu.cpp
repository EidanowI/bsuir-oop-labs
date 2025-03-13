#include "Menu.h"



extern bool G_should_quit;


void Menu::DrawMenu() {
	for (int i = 0; i < 68; i++, std::cout << ' ');
	std::cout << "\x1B[32mMENU\033[0m\n";
	int index;
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
	case FILL_OBJECT:
		if (m_state == CHOOSING_OBJECT) break;

		index =	InputSelection();

		if (m_state == MOVE_OBJECT) {
			int x, y;
			InputMovePos(x, y);

			AddOutputMsg("Move figure with name " + m_pCanvas->GetFigures()[index]->GetName());
			m_pCanvas->MoveFigure(index, x, y);
		}
		else if(m_state == DELETE_OBJECT){
			AddOutputMsg("Delete figure with name " + m_pCanvas->GetFigures()[index]->GetName());
			m_pCanvas->DeleteFigure(index);
		}
		else if (m_state == FILL_OBJECT) {
			std::cout << "Input fill char: ";
			char fill_char;
			std::cin >> fill_char;

			AddOutputMsg("Fill figure with name " + m_pCanvas->GetFigures()[index]->GetName() + "with ");
			m_pCanvas->FillFigure(index, fill_char);
		}
		break;
	case INPUT_DRAW_COMMAND:
		std::cout << "Choose figure: ";
		std::cout << "\x1B[33mE x y a b char\033[0m - draw ellipse; ";
		std::cout << "\x1B[33mR x y a b char\033[0m - draw rect; ";
		std::cout << "\x1B[33mT x y a b char\033[0m - draw triangle; ";
		std::cout << "\x1B[33mQ\033[0m - back; \n";
		std::cout << "\033[3;43;30mREMEMBER you can enter only integers, separated by space\033[0m\n";
		char a;
		std::cin >> a;
		if (a == 'Q') {
			m_state = CHOOSING_ACTION;
			break;
		}
		InputFigureParams(a);
		m_state = CHOOSING_ACTION;

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
	AddOutputMsg("");
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
	case 'F':
		m_state = FILL_OBJECT;
		break;
	case 'S'://Save
		m_pCanvas->Save(FileDialogWindow("Save file"));
		break;
	case 'L'://Load
		m_pCanvas->Load(FileDialogLoadWindow("Load file"));
		break;
	case 'Q':
		G_should_quit = true;
	default:
		break;
	}
}

std::string Menu::FileDialogWindow(std::string title) {
	OPENFILENAMEA ofn;
	char szFile[260];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.lpstrFilter = "Lab1 Files (*.lab1)\0*.lab1\0";
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrTitle = title.c_str();
	ofn.Flags = OFN_OVERWRITEPROMPT;

	if (GetSaveFileNameA(&ofn)) {
		return ofn.lpstrFile;
	}
	else{
		std::cerr << "\x1B[31mFILE DIALOG FAILED.\033[0m""" << std::endl;
	}
}
std::string Menu::FileDialogLoadWindow(std::string title) {
	OPENFILENAMEA ofn;
	char szFile[260];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.lpstrFilter = "Lab1 Files (*.lab1)\0*.lab1\0";
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrTitle = title.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileNameA(&ofn)) {
		return ofn.lpstrFile;
	}
	else {
		std::cerr << "\x1B[31mFILE DIALOG FAILED.\033[0m""" << std::endl;
	}
}

void Menu::InputFigureParams(char figure) {
	int params[4];

	if (figure != 'E' && figure != 'T' && figure != 'R')
	{
		AddOutputMsg("Invalid figure type!!!");
		return;
	}

	for (int i = 0; i < 4; i++) {
		std::string param_str;
		std::cin >> param_str;
		params[i] = std::stoi(param_str);
	}

	char fill_char;
	std::cin >> fill_char;

	IFigure* pFigure;

	switch (figure) {
	case 'T':
		if (!ValidateellipseParams(params[0], params[1], params[2], params[3])) {
			AddOutputMsg("Imposible to create triangle. Invalid params!!!");
			return;
		}
		pFigure = new Triangle(params[0], params[1], params[2], params[3], fill_char);
		AddOutputMsg("Draw triangle with square " + std::to_string(pFigure->GetSquare()) + " chars!");
		m_pCanvas->AddFigure(pFigure);
		break;
		break;
	case 'E':
		if (!ValidateellipseParams(params[0], params[1], params[2], params[3])) {
			AddOutputMsg("Imposible to create elipse. Invalid params!!!");
			return;
		}
		pFigure = new Elipse(params[0], params[1], params[2], params[3], fill_char);
		AddOutputMsg("Draw ellipse with square " + std::to_string(pFigure->GetSquare()) + " chars!");
		m_pCanvas->AddFigure(pFigure);
		break;
	case 'R':
		if (!ValidateRectParams(params[0], params[1], params[2], params[3])) {
			AddOutputMsg("Imposible to create rect. Invalid params!!!");
			return;
		}
		pFigure = new Rect(params[0], params[1], params[2], params[3], fill_char);
		AddOutputMsg("Draw rect with square " + std::to_string(pFigure->GetSquare()) + " chars!");
		m_pCanvas->AddFigure(pFigure);
		break;
	}
}

void Menu::AddOutputMsg(const std::string& msg) {
	m_output_msg = msg;
}

int Menu::InputSelection() {
	if (m_pCanvas->GetFigures().empty())
	{
		AddOutputMsg("No items to select");
		m_state = CHOOSING_ACTION;
		return -1;
	}
	std::cout << "\x1B[33mQ\033[0m - to quit!\n";
	std::cout << "Input object index\n";
	for (int i = 0; i < m_pCanvas->GetFigures().size(); i++) {
		std::cout << "\x1B[33m" << i << ". \033[0m" << m_pCanvas->GetFigures()[i]->GetName() << "\n";
	}

	while (true) {
		std::string inp;
		std::cin >> inp;

		if (inp[0] == 'Q') {
			m_state = CHOOSING_ACTION;
			return -1;
		}

		int index = std::stoi(inp);
		if (index >= 0 && index < m_pCanvas->GetFigures().size()) 
			return index;
		else {
			std::cout << "Invalid index!\n";
		}
	}
}

void Menu::InputMovePos(int& x, int& y) {
	while (true) {
		std::cout << "input x: ";
		std::string inp;
		std::cin >> inp;

		x = std::stoi(inp);
		if (x >= 0) break;
		std::cout << "Invalid x!\n";
	}

	while (true) {
		std::cout << "input y: ";
		std::string inp;
		std::cin >> inp;

		y = std::stoi(inp);
		if (y >= 0) break;
		std::cout << "Invalid y!\n";
	}
}