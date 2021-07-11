#pragma once

class Project;

#include "DBManager.h"

#include <string>

class Project {
  public:
	Project(int32_t createdBy, DBManager &db);
	Project(const std::string &name, const std::string &description, int32_t createdBy, DBManager &db);

	void setName(const std::string &name, int32_t changedBy);
	void setDescription(const std::string &description, int32_t changedBy);

	std::string getName() const;
	std::string getDescription() const;
	nanodbc::timestamp getCreatedOn() const;
	int32_t getCreatedBy() const;
	nanodbc::timestamp getLastChangedOn() const;
	int32_t getLastChangedBy() const;

  private:
	DBManager &db;
	std::string name;
	std::string description;
	const nanodbc::timestamp createdOn;
	const int32_t createdBy;
	nanodbc::timestamp lastChangedOn;
	int32_t lastChangedBy;

	void setName(const std::string &name);
	void setDescription(const std::string &description);

	template <typename T>
	friend void touch(T &, int32_t);
};
