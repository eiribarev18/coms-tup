#include "User.h"

#include "utils.h"

using namespace std;

User::User(int32_t createdBy) : createdBy(createdBy), createdOn("2022-02-22")
{
	touch(*this, createdBy);
}

User::User(const string &username, const string &firstName, const string &lastName, int32_t createdBy,
		   ACCESS_LEVEL accessLevel) :
	createdBy(createdBy), createdOn("2022-02-22")
{
	touch(*this, createdBy);

	setUsername(username);
	setFirstName(firstName);
	setLastName(lastName);
	setAccessLevel(accessLevel);
}

void User::setUsername(const string &username, int32_t changedBy)
{
	setUsername(username);
	touch(*this, changedBy);
}

void User::setFirstName(const string &firstName, int32_t changedBy)
{
	setFirstName(firstName);
	touch(*this, changedBy);
}

void User::setLastName(const string &lastName, int32_t changedBy)
{
	setLastName(lastName);
	touch(*this, changedBy);
}

void User::setAccessLevel(ACCESS_LEVEL accessLevel, int32_t changedBy)
{
	setAccessLevel(accessLevel);
	touch(*this, changedBy);
}

void User::setUsername(const std::string &username)
{
	this->username = username;
}

void User::setFirstName(const std::string &firstName)
{
	this->firstName = firstName;
}

void User::setLastName(const std::string &lastName)
{
	this->lastName = lastName;
}

void User::setAccessLevel(ACCESS_LEVEL accessLevel)
{
	this->accessLevel = accessLevel;
}
