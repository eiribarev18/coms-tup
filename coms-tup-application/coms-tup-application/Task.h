#pragma once

class Task;

#include "DBManager.h"

#include <string>

class Task {
  public:
	enum class STATUS
	{
		PENDING,
		IN_PROGRESS,
		COMPLETE
	};

	Task(int32_t createdBy, DBManager &db);
	Task(int32_t projectID, int32_t assigneeID, const std::string &title, const std::string &description, STATUS status,
		 int32_t createdBy, DBManager &db);

	void setProjectID(int32_t projectID, int32_t changedBy);
	void setAssigneeID(int32_t assigneeID, int32_t changedBy);
	void setTitle(const std::string &title, int32_t changedBy);
	void setDescription(const std::string &description, int32_t changedBy);
	void setStatus(STATUS status, int32_t changedBy);

	int32_t getID() const;
	int32_t getProjectID() const;
	int32_t getAssigneeID() const;
	std::string getTitle() const;
	std::string getDescription() const;
	STATUS getStatus() const;
	nanodbc::timestamp getCreatedOn() const;
	int32_t getCreatedBy() const;
	nanodbc::timestamp getLastChangedOn() const;
	int32_t getLastChangedBy() const;

  private:
	DBManager &db;
	const int32_t id;
	int32_t projectID;
	int32_t assigneeID;
	std::string title;
	std::string description;
	STATUS status;
	const nanodbc::timestamp createdOn;
	const int32_t createdBy;
	nanodbc::timestamp lastChangedOn;
	int32_t lastChangedBy;

	// DB Constructor
	Task(DBManager &db, int32_t id, int32_t projectID, int32_t assigneeID, const std::string &title,
		 const std::string &description, STATUS status, nanodbc::timestamp createdOn, int32_t createdBy,
		 nanodbc::timestamp lastChangedOn, int32_t lastChangedBy);

	void setProjectID(int32_t projectID);
	void setAssigneeID(int32_t assigneeID);
	void setTitle(const std::string &title);
	void setDescription(const std::string &description);
	void setStatus(STATUS status);

	template <typename T>
	friend void touch(T &, int32_t);
	friend class DBManager;
};
