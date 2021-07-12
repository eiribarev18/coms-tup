#pragma once

class Team;

#include "DBManager.h"

#include <string>

class Team {
  public:
	Team(int32_t createdBy, DBManager &db);
	Team(const std::string &name, int32_t createdBy, DBManager &db);

	void setName(const std::string &name, int32_t changedBy);

	int32_t getID() const;
	std::string getName() const;
	nanodbc::timestamp getCreatedOn() const;
	int32_t getCreatedBy() const;
	nanodbc::timestamp getLastChangedOn() const;
	int32_t getLastChangedBy() const;

  private:
	DBManager &db;
	const int32_t id;
	std::string name;
	const nanodbc::timestamp createdOn;
	const int32_t createdBy;
	nanodbc::timestamp lastChangedOn;
	int32_t lastChangedBy;

	// DB Constructor
	Team(DBManager &db, int32_t id, const std::string &name, nanodbc::timestamp createdOn, int32_t createdBy,
		 nanodbc::timestamp lastChangedOn, int32_t lastChangedBy);

	void setName(const std::string &name);

	template <typename T>
	friend void touch(T &, int32_t);
	friend class DBManager;
};
