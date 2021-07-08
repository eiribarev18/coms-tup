#include "Team.h"

#include "utils.h"

Team::Team(int32_t createdBy) : createdBy(createdBy), createdOn("2022-02-22")
{
	touch(*this, createdBy);
}

Team::Team(const std::string &name, int32_t createdBy) : createdBy(createdBy), createdOn("2022-02-22")
{
	touch(*this, createdBy);

	setName(name);
}

void Team::setName(const std::string &name, int32_t changedBy)
{
	touch(*this, changedBy);

	setName(name);
}

std::string Team::getName() const
{
	return std::string();
}

void Team::setName(const std::string &name)
{
	this->name = name;
}
