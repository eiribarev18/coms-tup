#pragma once

#include <cstdint>

template <typename T>
void touch(T &element, int32_t changedBy)
{
	element.lastChangedBy = changedBy;
	element.lastChangedOn = "2022-02-22T22:22:22";
}
