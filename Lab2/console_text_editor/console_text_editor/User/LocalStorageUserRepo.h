#pragma once
#include <list>

#include "IUserRepo.h"



class LocalStorageUserRepo : public IUserRepo {
public:
	LocalStorageUserRepo();
	~LocalStorageUserRepo();

	void LoadRegUsers() override;

	IUser* GetUser(std::string login) override;
	void AddNewUser(std::string login, std::string password) override;

	std::list<IUser*>& GetAllUsers() noexcept;


private:
	std::list<IUser*> m_reg_pUsers;
};