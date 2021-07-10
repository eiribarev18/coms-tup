#include "Task.h"

#include "utils.h"

Task::Task(int32_t createdBy, DBManager &db) : createdBy(createdBy), createdOn(db.getDate(false)), db(db)
{
	touch(*this, createdBy);
}

Task::Task(int32_t projectID, int32_t assigneeID, const std::string &title, const std::string &description,
		   STATUS status, int32_t createdBy, DBManager &db) :
	createdBy(createdBy), createdOn(db.getDate(false)), db(db)
{
	touch(*this, createdBy);

	setProjectID(projectID);
	setAssigneeID(assigneeID);
	setTitle(title);
	setDescription(description);
	setStatus(status);
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

int32_t Task::getProjectID() const
{
	return projectID;
}

int32_t Task::getAssigneeID() const
{
	return assigneeID;
}

std::string Task::getTitle() const
{
	return title;
}

std::string Task::getDescription() const
{
	return description;
}

Task::STATUS Task::getStatus() const
{
	return status;
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
