#pragma once

#include "ICommand.h"
#include "../Content/Content.h"



class DeleteCommand : public ICommand {
public:
	DeleteCommand(std::vector<char> data);
	~DeleteCommand();

	void Apply(char* pContent) override;

	void Delete(Content* pContent);

private:
	std::vector<char> m_data;
};