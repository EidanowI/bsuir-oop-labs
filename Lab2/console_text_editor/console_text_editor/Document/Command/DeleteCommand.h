#pragma once
#include <vector>

#include "ICommand.h"
//#include "../Content.h"



/*class DeleteCommand : public ICommand {
public:
	DeleteCommand(std::vector<Line> lines) {
		m_state_lines = lines;
	}
	~DeleteCommand() {

	}

	std::vector<Line> BringToState() override{
		return m_state_lines;
	}

	void Delete(Line& line, int pos_x) {
		if (pos_x > 0) {
			pos_x--;
			line.DelChar(pos_x);
		}
	}
private:
	std::vector<Line> m_state_lines;
};*/