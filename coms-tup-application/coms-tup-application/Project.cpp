#include "Project.h"

#include "utils.h"

using namespace std;

Project::Project(int32_t createdBy, DBManager &db) : createdBy(createdBy), createdOn(db.getDate()), db(db)
{
	touch(*this, createdBy);
}

Project::Project(const string &name, const string &description, int32_t createdBy, DBManager &db) :
	createdBy(createdBy), createdOn(db.getDate()), db(db)
{
	touch(*this, createdBy);

	setName(name);
	setDescription(description);
}

void Project::setName(const string &name, int32_t changedBy)
{
	touch(*this, changedBy);

	setName(name);
}

void Project::setDescription(const string &description, int32_t changedBy)
{
	touch(*this, changedBy);

	setDescription(description);
}

string Project::getName() const
{
	return name;
}

string Project::getDescription() const
{
	return description;
}

nanodbc::timestamp Project::getCreatedOn() const
{
	return createdOn;
}

int32_t Project::getCreatedBy() const
{
	return createdBy;
}

nanodbc::timestamp Project::getLastChangedOn() const
{
	return lastChangedOn;
}

int32_t Project::getLastChangedBy() const
{
	return lastChangedBy;
}

void Project::setName(const string &name)
{
	this->name = name;
}

void Project::setDescription(const string &description)
{
	this->description = description;
}
