#pragma once
#include <vector>

#include "ICommand.h"
#include "../Content/Content.h"



class AddCharCommand : public ICommand {
public:
	AddCharCommand(std::vector<char> data) {
		m_data = data;
	}
	~AddCharCommand() {

	}

	void BringToState(Content* pContent)  override {
		pContent->GetData() = m_data;
	}

	void AddChar(Content* pContent, char ch) {
		pContent->AddChar(ch);
	}

private:
	std::vector<char> m_data;
};