#pragma once
#include <iostream>



class IFormator {
public:
	virtual ~IFormator() {};

	virtual void CharDecorate(int cursor_pos) = 0;
};


class Formator : public IFormator {
public:
	Formator() {

	}
	~Formator() {

	}

	void CharDecorate(int cursor_pos) override {

	}
};


class BaseFormator : public IFormator {
public:
	BaseFormator(IFormator* pOrigin) : m_pOrigin(pOrigin){

	}
	~BaseFormator() {
		delete m_pOrigin;
	}

	void CharDecorate(int cursor_pos) override {
		return m_pOrigin->CharDecorate(cursor_pos);
	}
private:
	IFormator* m_pOrigin;
};


class BoldFormater : public BaseFormator {
public:
	BoldFormater(int beg, int end, IFormator* pOrigin) : BaseFormator(pOrigin) {
		m_begin = beg;
		m_end = end;
	}
	~BoldFormater() {

	}

	void CharDecorate(int cursor_pos) override {
		if (m_begin == cursor_pos) {
			std::cout << "**";
		}
		if (m_end == cursor_pos) {
			std::cout << "**";
		}

		return BaseFormator::CharDecorate(cursor_pos);
	}

private:
	int m_begin;
	int m_end;
};


class ItalicFormater : public BaseFormator {
public:
	ItalicFormater(int beg, int end, IFormator* pOrigin) : BaseFormator(pOrigin) {
		m_begin = beg;
		m_end = end;
	}
	~ItalicFormater() {

	}

	void CharDecorate(int cursor_pos) override {
		if (m_begin == cursor_pos) {
			std::cout << "*";
		}
		if (m_end == cursor_pos) {
			std::cout << "*";
		}

		return BaseFormator::CharDecorate(cursor_pos);
	}

private:
	int m_begin;
	int m_end;
};


class UnderlineFormater : public BaseFormator {
public:
	UnderlineFormater(int beg, int end, IFormator* pOrigin) : BaseFormator(pOrigin) {
		m_begin = beg;
		m_end = end;
	}
	~UnderlineFormater() {

	}

	void CharDecorate(int cursor_pos) override {
		if (m_begin == cursor_pos) {
			std::cout << "_";
		}
		if (m_end == cursor_pos) {
			std::cout << "_";
		}

		return BaseFormator::CharDecorate(cursor_pos);
	}

private:
	int m_begin;
	int m_end;
};