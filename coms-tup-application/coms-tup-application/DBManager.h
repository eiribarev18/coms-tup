#pragma once

#include <nanodbc.h>

class DBManager;

#include "Project.h"
#include "Task.h"
#include "Team.h"
#include "User.h"
#include "WorkLog.h"

class DBManager {
  public:
	DBManager() = default;
	DBManager(const std::string &connectionString);

	bool insert(const Project &project);
	bool insert(const Task &task);
	bool insert(const Team &team);
	bool insert(const User &user, const std::string &password);
	bool insert(const WorkLog &workLog);

	bool updateByID(const Project &project);
	bool updateByID(const Task &task);
	bool updateByID(const Team &team);
	bool updateByID(const User &user);
	bool updateByID(const User &user, const std::string &password);

	bool deleteByID(const Project &project);
	bool deleteByID(const Task &task);
	bool deleteByID(const Team &team);
	bool deleteByID(const User &user);

	nanodbc::timestamp getDate(bool includeTime = false);

  private:
	nanodbc::connection connection;
};
