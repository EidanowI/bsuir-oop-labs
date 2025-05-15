#pragma once
#include <string>
#include <vector>

#include "../User/User.h"
#include "../User/LocalStorageUserRepo.h"
#include "../Saver/ISaverStrategy.h"

#include "Content/Content.h"



struct EditPermisionLayer {
	unsigned int _login_hash;
	time_t _lastTime_edit;
};


class Document {
	friend class LocalSaver;
public:
	Document(LocalStorageUserRepo* pUserRepo, User* pUser, const std::string& path);///for exist document
	Document(LocalStorageUserRepo* pUserRepo, User* pUser);///for new document
	~Document();

	void PrintAllUsers(LocalStorageUserRepo* pUserRepo);
	void ChangePermissionForUser(LocalStorageUserRepo* pUserRepo, User* pUser);


	void ImportFromFile();
	void ExportToFile();

	void SaveDocument(ISaverStrategy* saver);///Strategy patern

	bool GetIsEditable() {
		return m_isEditable;
	}

	void Edit(User* pUser);

private:
	bool m_isEditable = false;

	std::vector<EditPermisionLayer> m_permisionLayers;

	bool m_isEdited = false;
	Content m_content;
};