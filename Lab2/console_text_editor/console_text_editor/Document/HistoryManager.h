#pragma once
#include "Command/ICommand.h"
#include <vector>



class HestoryManager {
public:
	HestoryManager() {
		currentPos = -1;
	}
	~HestoryManager() {
		for (int i = 0; i < history.size(); i++) {
			delete history[i];
		}
	}

	void AddCommand(ICommand* pCommand) {
		if (currentPos != static_cast<int>(history.size()) - 1) {
			history.erase(history.begin() + currentPos + 1, history.end());
		}
		history.push_back(pCommand);
		currentPos = history.size() - 1;
	}

	ICommand* Undo() {
		if (history.empty() || currentPos <= 0) {
			return 0;
		}
		--currentPos;
		return history[currentPos];
	}
	ICommand* Redo() {
		if (history.empty() || currentPos >= static_cast<int>(history.size()) - 1) {
			return 0; // 
		}
		++currentPos;
		return history[currentPos];
	}


private:
	std::vector<ICommand*> history;
	int currentPos = -1;
};