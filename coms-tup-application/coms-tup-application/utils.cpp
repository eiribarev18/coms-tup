#include "utils.h"

#include <ctime>

using namespace std;

string to_string(nanodbc::timestamp timestamp, bool includeTime)
{
	tm t;
	char out[20];

	t.tm_year = timestamp.year - 1900;
	t.tm_mon = timestamp.month - 1;
	t.tm_mday = timestamp.day;
	t.tm_hour = timestamp.hour;
	t.tm_min = timestamp.min;
	t.tm_sec = timestamp.sec;

	if (includeTime)
		strftime(out, 20, "%F %T", &t);
	else
		strftime(out, 11, "%F", &t);

	return out;
}

std::string to_string(User::ACCESS_LEVEL accessLevel)
{
	switch ((int)accessLevel) {
		case 0:
			return "USER";
		case 1:
			return "ADMIN";
		case 2:
			return "ROOT ADMIN";
	}
}
