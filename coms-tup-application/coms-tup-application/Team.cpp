#include "Team.h"

#include "utils.h"

using namespace std;

Team::Team(int32_t createdBy) : createdBy(createdBy), createdOn("2022-02-22")
{
	touch(*this, createdBy);
}

Team::Team(const string &name, int32_t createdBy) : createdBy(createdBy), createdOn("2022-02-22")
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
