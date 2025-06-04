#include <Windows.h>
#include <iostream>

#include "FileDialog.h"



std::string FileDialog::FileDialogLoad(std::string title, const char* filter) {
	OPENFILENAMEA ofn;
	char szFile[260];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.lpstrFilter = filter;
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
std::string FileDialog::FileDialogSave(std::string title, const char* filter) {
	OPENFILENAMEA ofn;
	char szFile[260];
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.lpstrFilter = filter;
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrTitle = title.c_str();
	ofn.Flags = OFN_OVERWRITEPROMPT;

	if (GetSaveFileNameA(&ofn)) {
		return ofn.lpstrFile;
	}
	else {
		std::cerr << "\x1B[31mFILE DIALOG FAILED.\033[0m""" << std::endl;
	}
}