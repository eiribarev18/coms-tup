#include "Team.h"

#include "utils.h"

using namespace std;

Team::Team(int32_t createdBy, DBManager &db) : createdBy(createdBy), createdOn(db.getDate()), db(db), id(0)
{
	touch(*this, createdBy);
}

Team::Team(const string &name, int32_t createdBy, DBManager &db) :
	createdBy(createdBy), createdOn(db.getDate()), db(db), id(0)
{
	touch(*this, createdBy);

	setName(name);
}

Team::Team(DBManager &db, int32_t id, const std::string &name, nanodbc::timestamp createdOn, int32_t createdBy,
		   nanodbc::timestamp lastChangedOn, int32_t lastChangedBy) :
	db(db),
	id(id),
	name(name),
	createdOn(createdOn),
	createdBy(createdBy),
	lastChangedOn(lastChangedOn),
	lastChangedBy(lastChangedBy)
{
}

void Team::setName(const string &name, int32_t changedBy)
{
	touch(*this, changedBy);

	setName(name);
}

int32_t Team::getID() const
{
	return id;
}

string Team::getName() const
{
	return name;
}

nanodbc::timestamp Team::getCreatedOn() const
{
	return createdOn;
}

int32_t Team::getCreatedBy() const
{
	return createdBy;
}

nanodbc::timestamp Team::getLastChangedOn() const
{
	return lastChangedOn;
}

int32_t Team::getLastChangedBy() const
{
	return lastChangedBy;
}

void Team::setName(const string &name)
{
	this->name = name;
}
