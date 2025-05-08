#include "AddCharCommand.h"



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