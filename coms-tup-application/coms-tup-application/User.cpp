#include "User.h"

#include "utils.h"

using namespace std;

User::User(int32_t createdBy, DBManager &db) : createdBy(createdBy), createdOn(db.getDate(false)), db(db)
{
	touch(*this, createdBy);
}

User::User(const string &username, const string &firstName, const string &lastName, int32_t createdBy,
		   ACCESS_LEVEL accessLevel, DBManager &db) :
	createdBy(createdBy), createdOn(db.getDate(false)), db(db)
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

string User::getUsername() const
{
	return username;
}

string User::getFirstName() const
{
	return firstName;
}

string User::getLastName() const
{
	return lastName;
}

User::ACCESS_LEVEL User::getAccessLevel() const
{
	return accessLevel;
}

void User::setUsername(const string &username)
{
	this->username = username;
}

void User::setFirstName(const string &firstName)
{
	this->firstName = firstName;
}

void User::setLastName(const string &lastName)
{
	this->lastName = lastName;
}

void User::setAccessLevel(ACCESS_LEVEL accessLevel)
{
	this->accessLevel = accessLevel;
}
