#pragma once

#include <string>
#include "DBManager.h"

class Team {
  public:
	Team(int32_t createdBy, DBManager &db);
	Team(const std::string &name, int32_t createdBy, DBManager &db);

	void setName(const std::string &name, int32_t changedBy);

	std::string getName() const;

  private:
	DBManager &db;
	std::string name;
	const std::string createdOn;
	const int32_t createdBy;
	std::string lastChangedOn;
	int32_t lastChangedBy;

	void setName(const std::string &name);

	template <typename T>
	friend void touch(T &, int32_t);
};
