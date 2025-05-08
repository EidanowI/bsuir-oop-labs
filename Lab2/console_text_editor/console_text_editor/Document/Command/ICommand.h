#pragma once



class ICommand {
public:
	virtual void Apply(char* pContent) = 0;
};