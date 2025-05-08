#pragma once
#include <vector>

#include "ICommand.h"
//#include "../Content.h"



/*class AddCharCommand : public ICommand {
public:
	AddCharCommand(std::vector<Line> lines) {
		m_state_lines = lines;
	}
	~AddCharCommand() {

	}

	std::vector<Line> BringToState() override {
		return m_state_lines;
	}

	void AddChar(char ch, Line& line, int pos_x) {
		line.AddChar(ch, pos_x);
	}
private:
	std::vector<Line> m_state_lines;
};*/