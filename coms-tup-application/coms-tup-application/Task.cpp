#include "Task.h"

#include "utils.h"

using namespace std;

Task::Task(int32_t createdBy, DBManager &db) : createdBy(createdBy), createdOn(db.getDate()), db(db), id(0)
{
	touch(*this, createdBy);
}

Task::Task(int32_t projectID, int32_t assigneeID, const std::string &title, const std::string &description,
		   STATUS status, int32_t createdBy, DBManager &db) :
	createdBy(createdBy), createdOn(db.getDate()), db(db), id(0)
{
	touch(*this, createdBy);

	setProjectID(projectID);
	setAssigneeID(assigneeID);
	setTitle(title);
	setDescription(description);
	setStatus(status);
}

Task::Task(DBManager &db, int32_t id, int32_t projectID, int32_t assigneeID, const string &title,
		   const string &description, STATUS status, nanodbc::timestamp createdOn, int32_t createdBy,
		   nanodbc::timestamp lastChangedOn, int32_t lastChangedBy) :
	db(db),
	id(id),
	projectID(projectID),
	assigneeID(assigneeID),
	title(title),
	description(description),
	status(status),
	createdOn(createdOn),
	createdBy(createdBy),
	lastChangedOn(lastChangedOn),
	lastChangedBy(lastChangedBy)
{
}

void Task::setProjectID(int32_t projectID, int32_t changedBy)
{
	touch(*this, changedBy);

	setProjectID(projectID);
}

void Task::setAssigneeID(int32_t assigneeID, int32_t changedBy)
{
	touch(*this, changedBy);

	setAssigneeID(assigneeID);
}

void Task::setTitle(const std::string &title, int32_t changedBy)
{
	touch(*this, changedBy);

	setTitle(title);
}

void Task::setDescription(const std::string &description, int32_t changedBy)
{
	touch(*this, changedBy);

	setDescription(description);
}

void Task::setStatus(STATUS status, int32_t changedBy)
{
	touch(*this, changedBy);

	setStatus(status);
}

int32_t Task::getID() const
{
	return id;
}

int32_t Task::getProjectID() const
{
	return projectID;
}

int32_t Task::getAssigneeID() const
{
	return assigneeID;
}

string Task::getTitle() const
{
	return title;
}

string Task::getDescription() const
{
	return description;
}

Task::STATUS Task::getStatus() const
{
	return status;
}

nanodbc::timestamp Task::getCreatedOn() const
{
	return createdOn;
}

int32_t Task::getCreatedBy() const
{
	return createdBy;
}

nanodbc::timestamp Task::getLastChangedOn() const
{
	return lastChangedOn;
}

int32_t Task::getLastChangedBy() const
{
	return lastChangedBy;
}

void Task::setProjectID(int32_t projectID)
{
	this->projectID = projectID;
}

void Task::setAssigneeID(int32_t assigneeID)
{
	this->assigneeID = assigneeID;
}

void Task::setTitle(const std::string &title)
{
	this->title = title;
}

void Task::setDescription(const std::string &description)
{
	this->description = description;
}

void Task::setStatus(STATUS status)
{
	this->status = status;
}
