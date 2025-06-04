#include "AddCharCommand.h"
#include "DeleteChar.h"
#include "PasteCommand.h"



AddCharCommand::AddCharCommand(std::vector<char> data) {
	m_data = data;
}
AddCharCommand::~AddCharCommand() {

}

void AddCharCommand::Apply(char* pContent) {
	((Content*)pContent)->GetData() = m_data;
}

void AddCharCommand::AddChar(Content* pContent, char ch) {
	pContent->AddChar(ch);
}


DeleteCommand::DeleteCommand(std::vector<char> data) {
	m_data = data;
}
DeleteCommand::~DeleteCommand() {

}

void DeleteCommand::Apply(char* pContent) {
	((Content*)pContent)->GetData() = m_data;
}

void DeleteCommand::Delete(Content* pContent) {
	pContent->DeleteChar();
}

PasteCommand::PasteCommand(std::vector<char> data) {
	m_data = data;
}
PasteCommand::~PasteCommand() {

}

void PasteCommand::Apply(char* pContent) {
	((Content*)pContent)->GetData() = m_data;
}

void PasteCommand::Paste(Content* pContent) {
	pContent->Paste();
}