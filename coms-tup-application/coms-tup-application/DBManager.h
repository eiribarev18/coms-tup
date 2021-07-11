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

	bool update(const Project &project);
	bool update(const Task &task);

	nanodbc::timestamp getDate(bool includeTime = false);

  private:
	nanodbc::connection connection;
};
