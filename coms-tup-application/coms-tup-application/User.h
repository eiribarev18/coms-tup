#pragma once

class User;

#include "DBManager.h"

#include <string>

class User {
  public:
	enum class ACCESS_LEVEL
	{
		USER,
		ADMIN,
		ROOT_ADMIN
	};

	User(int32_t createdBy, DBManager &db);
	User(const std::string &username, const std::string &firstName, const std::string &lastName, int32_t createdBy,
		 ACCESS_LEVEL accessLevel, DBManager &db);

	void setUsername(const std::string &username, int32_t changedBy);
	void setFirstName(const std::string &firstName, int32_t changedBy);
	void setLastName(const std::string &lastName, int32_t changedBy);
	void setAccessLevel(ACCESS_LEVEL accessLevel, int32_t changedBy);

	int32_t getID() const;
	std::string getUsername() const;
	std::string getFirstName() const;
	std::string getLastName() const;
	ACCESS_LEVEL getAccessLevel() const;
	nanodbc::timestamp getCreatedOn() const;
	int32_t getCreatedBy() const;
	nanodbc::timestamp getLastChangedOn() const;
	int32_t getLastChangedBy() const;

  private:
	DBManager &db;
	const int32_t id;
	std::string username;
	std::string firstName;
	std::string lastName;
	const nanodbc::timestamp createdOn;
	const int32_t createdBy;
	nanodbc::timestamp lastChangedOn;
	int32_t lastChangedBy;
	ACCESS_LEVEL accessLevel = ACCESS_LEVEL::USER;

	// DB Constructor
	User(DBManager &db, int32_t id, const std::string &username, const std::string &firstName,
		 const std::string &lastName, nanodbc::timestamp createdOn, int32_t createdBy, nanodbc::timestamp lastChangedOn,
		 int32_t lastChangedBy, ACCESS_LEVEL accessLevel);

	void setUsername(const std::string &username);
	void setFirstName(const std::string &firstName);
	void setLastName(const std::string &lastName);
	void setAccessLevel(ACCESS_LEVEL accessLevel);

	template <typename T>
	friend void touch(T &, int32_t);
	friend class DBManager;
};
