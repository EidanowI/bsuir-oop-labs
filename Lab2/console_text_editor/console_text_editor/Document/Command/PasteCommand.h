#pragma once

#include "ICommand.h"
#include "../Content/Content.h"



class PasteCommand : public ICommand {
public:
	PasteCommand(std::vector<char> data);
	~PasteCommand();

	void Apply(char* pContent) override;

	void Paste(Content* pContent);

private:
	std::vector<char> m_data;
};