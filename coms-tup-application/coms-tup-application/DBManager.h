#pragma once

#include <nanodbc.h>

class DBManager {
  public:
	DBManager() = default;
	DBManager(const std::string &connectionString);

	std::string getDate(bool includeTime = true);

  private:
	nanodbc::connection connection;
};
