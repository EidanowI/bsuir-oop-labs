#include <iostream>

#include "EditPermissionOpener.h"
#include "ViewPermissionOpener.h"



EditPermissionOpener::EditPermissionOpener() {

}
EditPermissionOpener::~EditPermissionOpener() {

}

void EditPermissionOpener::OpenDocument(std::string path) {
	std::cout << "Im Editor" << '\n';
	char ch;
	std::cin >> ch;
}


ViewPermissionOpener::ViewPermissionOpener() {

}
ViewPermissionOpener::~ViewPermissionOpener() {

}

void ViewPermissionOpener::OpenDocument(std::string path) {
	std::cout << "Im Viewer" << '\n';
	char ch;
	std::cin >> ch;
}