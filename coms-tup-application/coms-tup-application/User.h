#pragma once

#include <iostream>

class User {
  public:
	enum class ACCESS_LEVEL
	{
		USER,
		ADMIN,
		ROOT_ADMIN
	};

	User(int32_t createdBy);
	User(const std::string &username, const std::string &firstName, const std::string &lastName, int32_t createdBy,
		 ACCESS_LEVEL accessLevel = ACCESS_LEVEL::USER);

	void setUsername(const std::string &username, int32_t changedBy);
	void setFirstName(const std::string &firstName, int32_t changedBy);
	void setLastName(const std::string &lastName, int32_t changedBy);
	void setAccessLevel(ACCESS_LEVEL accessLevel, int32_t changedBy);

	std::string getUsername() const;
	std::string getFirstName() const;
	std::string getLastName() const;
	ACCESS_LEVEL getAccessLevel() const;

  private:
	std::string username;
	std::string firstName;
	std::string lastName;
	const std::string createdOn;
	const int32_t createdBy;
	std::string lastChangedOn;
	int32_t lastChangedBy;
	ACCESS_LEVEL accessLevel = ACCESS_LEVEL::USER;

	void setUsername(const std::string &username);
	void setFirstName(const std::string &firstName);
	void setLastName(const std::string &lastName);
	void setAccessLevel(ACCESS_LEVEL accessLevel);

	template <typename T>
	friend void touch(T &, int32_t);
};
