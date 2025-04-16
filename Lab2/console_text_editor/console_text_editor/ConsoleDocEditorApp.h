#pragma once
#include "User/IUserRepo.h"



class ConsoleDocEditorApp {
public:
	ConsoleDocEditorApp();
	~ConsoleDocEditorApp();

	void Run();

private:
	IUserRepo* m_pUser_repo = nullptr;
	IUser* m_pUser = nullptr;
};