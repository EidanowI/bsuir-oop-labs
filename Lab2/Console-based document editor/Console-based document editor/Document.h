#pragma once
#include <chrono>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <ctime>



extern bool G_is_editor_rinning;

class Document {
public:
	void Edit();

private:
	bool is_key_presed[256]{};
	int is_key_presed_s[256]{};
};