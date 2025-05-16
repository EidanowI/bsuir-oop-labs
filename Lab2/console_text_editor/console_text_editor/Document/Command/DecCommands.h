#pragma once

#include "ICommand.h"
#include "../Content/Content.h"
#include "../Content/Decorator/Decorator.h"



class MakeBold : public ICommand {
public:
	MakeBold(IFormator* pFormator) {
		m_pFormator = pFormator;
	}
	~MakeBold() {

	}

	void Apply(char* pContent) override {
		((Content*)pContent)->m_pFormator = m_pFormator;
	}

	void AddBold(Content* pContent, int beg, int end) {
		((Content*)pContent)->m_pFormator = new BoldFormater(beg, end, m_pFormator);
		((Content*)pContent)->Print();
	}

private:
	IFormator* m_pFormator;
};

class MakeItalic : public ICommand {
public:
	MakeItalic(IFormator* pFormator) {
		m_pFormator = pFormator;
	}
	~MakeItalic(){}

	void Apply(char* pContent) override {
		((Content*)pContent)->m_pFormator = m_pFormator;
	}

	void AddBold(Content* pContent, int beg, int end) {
		((Content*)pContent)->m_pFormator = new ItalicFormater(beg, end, m_pFormator);
		((Content*)pContent)->Print();
	}

private:
	IFormator* m_pFormator;
};

class MakeUnder : public ICommand {
public:
	MakeUnder(IFormator* pFormator) {
		m_pFormator = pFormator;
	}
	~MakeUnder(){}

	void Apply(char* pContent) override {
		((Content*)pContent)->m_pFormator = m_pFormator;
	}

	void AddBold(Content* pContent, int beg, int end) {
		((Content*)pContent)->m_pFormator = new UnderlineFormater(beg, end, m_pFormator);
		((Content*)pContent)->Print();
	}

private:
	IFormator* m_pFormator;
};