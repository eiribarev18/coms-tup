#include "Project.h"

#include "utils.h"

using namespace std;

Project::Project(int32_t createdBy) : createdBy(createdBy), createdOn("2022-02-22")
{
	touch(*this, createdBy);
}

Project::Project(const string &name, const string &description, int32_t createdBy) :
	createdBy(createdBy), createdOn("2022-02-22")
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

void Project::setName(const string &name)
{
	this->name = name;
}

void Project::setDescription(const string &description)
{
	this->description = description;
}
