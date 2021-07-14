#pragma once

#include "DBManager.h"

#include <cstdint>

template <typename T>
void touch(T &element, int32_t changedBy)
{
	element.lastChangedBy = changedBy;
	element.lastChangedOn = element.db.getDate(true);
}

std::string to_string(nanodbc::timestamp timestamp, bool includeTime = true);
std::string to_string(User::ACCESS_LEVEL accessLevel);
