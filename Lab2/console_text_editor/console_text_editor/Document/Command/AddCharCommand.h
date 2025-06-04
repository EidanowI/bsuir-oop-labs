#pragma once

#include "ICommand.h"
#include "../Content/Content.h"



class AddCharCommand : public ICommand {
public:
	AddCharCommand(std::vector<char> data);
	~AddCharCommand();

	void Apply(char* pContent) override;

	void AddChar(Content* pContent, char ch);

private:
	std::vector<char> m_data;
};