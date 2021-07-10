#pragma once

#include <string>

class WorkLog {
  public:
	WorkLog(int32_t taskID, int32_t userID, int8_t hoursSpent);

	int32_t getTaskID() const;
	int32_t getUserID() const;
	std::string getDate() const;
	int8_t getHoursSpent() const;

  private:
	const int32_t taskID;
	const int32_t userID;
	const std::string date;
	const int8_t hoursSpent;
};
