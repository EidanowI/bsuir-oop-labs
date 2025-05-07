#pragma once
#include <string>

#include "../User/User.h"
#include "../User/LocalStorageUserRepo.h"
#include "Content.h"
#include "../Saver/ISaverStrategy.h"




struct EditPermisionLayer {
	unsigned int _login_hash;
	time_t _lastTime_edit;
};


class Document {
public:
	Document(LocalStorageUserRepo* pUserRepo, User* pUser, const std::string& path);///for exist document
	Document(LocalStorageUserRepo* pUserRepo, User* pUser);///for new document
	~Document();

	void PrintAllUsers(LocalStorageUserRepo* pUserRepo);
	void ChangePermissionForUser(LocalStorageUserRepo* pUserRepo, User* pUser);

	void SaveDocument(ISaverStrategy* saver);///Strategy patern

	bool GetIsEditable() {
		return m_isEditable;
	}
private:
	bool m_isEditable = false;

	std::vector<EditPermisionLayer> m_permisionLayers;

	//bool m_isEditable = false;///TODO if opener viewer then we do not save author

	//bool m_isDocument_content_changed = false;
	//std::string m_opener;

	//std::string m_author;
	//std::string m_edit_date;

	//Content m_content;
};