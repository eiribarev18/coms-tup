#include "WorkLog.h"

WorkLog::WorkLog(int32_t taskID, int32_t userID, int8_t hoursSpent, DBManager &db) :
	taskID(taskID), userID(userID), date(db.getDate()), hoursSpent(hoursSpent), db(db), id(0)
{
}

WorkLog::WorkLog(DBManager &db, int32_t id, int32_t taskID, int32_t userID, nanodbc::timestamp date,
				 int8_t hoursSpent) :
	db(db), id(id), taskID(taskID), userID(userID), date(date), hoursSpent(hoursSpent)
{
}

int32_t WorkLog::getID() const
{
	return id;
}

int32_t WorkLog::getTaskID() const
{
	return taskID;
}

int32_t WorkLog::getUserID() const
{
	return userID;
}

nanodbc::timestamp WorkLog::getDate() const
{
	return date;
}

int8_t WorkLog::getHoursSpent() const
{
	return hoursSpent;
}
