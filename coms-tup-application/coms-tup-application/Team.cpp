#include "Team.h"

#include "utils.h"

using namespace std;

Team::Team(int32_t createdBy, DBManager &db) : createdBy(createdBy), createdOn(db.getDate(false)), db(db)
{
	touch(*this, createdBy);
}

Team::Team(const string &name, int32_t createdBy, DBManager &db) :
	createdBy(createdBy), createdOn(db.getDate(false)), db(db)
{
	touch(*this, createdBy);

	setName(name);
}

void Team::setName(const string &name, int32_t changedBy)
{
	touch(*this, changedBy);

	setName(name);
}

string Team::getName() const
{
	return name;
}

void Team::setName(const string &name)
{
	this->name = name;
}
