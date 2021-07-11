#pragma once

class WorkLog;

#include "DBManager.h"

#include <string>

class WorkLog {
  public:
	WorkLog(int32_t taskID, int32_t userID, int8_t hoursSpent, DBManager &db);

	int32_t getID() const;
	int32_t getTaskID() const;
	int32_t getUserID() const;
	nanodbc::timestamp getDate() const;
	int8_t getHoursSpent() const;

  private:
	DBManager &db;
	const int32_t id;
	const int32_t taskID;
	const int32_t userID;
	const nanodbc::timestamp date;
	const int8_t hoursSpent;
};
