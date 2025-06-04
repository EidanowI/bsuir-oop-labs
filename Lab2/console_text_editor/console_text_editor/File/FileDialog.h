#pragma once
#include <string>



namespace FileDialog {
	std::string FileDialogLoad(std::string title, const char* filter = "Lab2 Files (*.lab2)\0*.lab2\0");
	std::string FileDialogSave(std::string title, const char* filter = "Lab2 Files (*.lab2)\0*.lab2\0");
}