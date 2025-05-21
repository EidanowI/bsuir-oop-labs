#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>



struct Specs {
	int beg;
	int end;
	char type;
};

class IFormator {
public:
	virtual ~IFormator() {};

	virtual void CharDecorate(int cursor_pos) = 0;
	virtual void CharDecorate(int cursor_pos, std::ofstream& ofs) = 0;
	virtual void CharDecorate(int cursor_pos, std::stringstream& ofs) = 0;
	virtual std::vector<Specs>* CalcDecsCount(std::vector<Specs>*) = 0;
};


class Formator : public IFormator {
public:
	Formator() {

	}
	~Formator() {

	}

	void CharDecorate(int cursor_pos) override {

	}
	void CharDecorate(int cursor_pos, std::ofstream& ofs) override {

	}
	void CharDecorate(int cursor_pos, std::stringstream& ofs) override {

	}
	std::vector<Specs>* CalcDecsCount(std::vector<Specs>* specs)override {
		return specs;
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
	void CharDecorate(int cursor_pos, std::ofstream& ofs) override {
		return m_pOrigin->CharDecorate(cursor_pos, ofs);
	}
	void CharDecorate(int cursor_pos, std::stringstream& ofs) override {
		return m_pOrigin->CharDecorate(cursor_pos, ofs);
	}
	std::vector<Specs>* CalcDecsCount(std::vector<Specs>* specs)override {
		return m_pOrigin->CalcDecsCount(specs);
	}
protected:
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
	void CharDecorate(int cursor_pos, std::ofstream& ofs) override {
		if (m_begin == cursor_pos) {
			ofs << "**";
		}
		if (m_end == cursor_pos) {
			ofs << "**";
		}

		return BaseFormator::CharDecorate(cursor_pos, ofs);
	}
	void CharDecorate(int cursor_pos, std::stringstream& ofs) override {
		if (m_begin == cursor_pos) {
			ofs << "**";
		}
		if (m_end == cursor_pos) {
			ofs << "**";
		}

		return BaseFormator::CharDecorate(cursor_pos, ofs);
	}

	std::vector<Specs>* CalcDecsCount(std::vector<Specs>* specs)override {
		specs->push_back({ m_begin, m_end, 'B' });
		return m_pOrigin->CalcDecsCount(specs);
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
	void CharDecorate(int cursor_pos, std::ofstream& ofs) override {
		if (m_begin == cursor_pos) {
			ofs << "*";
		}
		if (m_end == cursor_pos) {
			ofs << "*";
		}

		return BaseFormator::CharDecorate(cursor_pos, ofs);
	}
	void CharDecorate(int cursor_pos, std::stringstream& ofs) override {
		if (m_begin == cursor_pos) {
			ofs << "*";
		}
		if (m_end == cursor_pos) {
			ofs << "*";
		}

		return BaseFormator::CharDecorate(cursor_pos, ofs);
	}
	std::vector<Specs>* CalcDecsCount(std::vector<Specs>* specs)override {
		specs->push_back({ m_begin, m_end, 'I' });
		return m_pOrigin->CalcDecsCount(specs);
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
	void CharDecorate(int cursor_pos, std::ofstream& ofs) override {
		if (m_begin == cursor_pos) {
			ofs << "_";
		}
		if (m_end == cursor_pos) {
			ofs << "_";
		}

		return BaseFormator::CharDecorate(cursor_pos, ofs);
	}
	void CharDecorate(int cursor_pos, std::stringstream& ofs) override {
		if (m_begin == cursor_pos) {
			ofs << "_";
		}
		if (m_end == cursor_pos) {
			ofs << "_";
		}

		return BaseFormator::CharDecorate(cursor_pos, ofs);
	}
	std::vector<Specs>* CalcDecsCount(std::vector<Specs>* specs)override {
		specs->push_back({ m_begin, m_end, 'U' });
		return m_pOrigin->CalcDecsCount(specs);
	}

private:
	int m_begin;
	int m_end;
};