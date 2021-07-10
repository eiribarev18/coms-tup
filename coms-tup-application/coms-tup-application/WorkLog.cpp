#include "WorkLog.h"

WorkLog::WorkLog(int32_t taskID, int32_t userID, int8_t hoursSpent, DBManager &db) :
	taskID(taskID), userID(userID), date(db.getDate(false)), hoursSpent(hoursSpent), db(db)
{
}

int32_t WorkLog::getTaskID() const
{
	return taskID;
}

int32_t WorkLog::getUserID() const
{
	return userID;
}

std::string WorkLog::getDate() const
{
	return date;
}

int8_t WorkLog::getHoursSpent() const
{
	return hoursSpent;
}
