#pragma once
#include <string>

#include "Content.h"



class Document {
public:
	Document(bool is_editable, char* opener);
	~Document();

	void Open(std::string name);
	void Save();
	void Edit();

	std::string& GetAuthor();
	std::string& GetEditDate();
	
private:
	bool m_isEditable = false;///TODO if opener viewer then we do not save author

	//bool m_isDocument_content_changed = false;
	std::string m_opener;

	std::string m_author;
	std::string m_edit_date;

	Content m_content;
};