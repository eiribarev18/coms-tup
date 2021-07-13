#pragma once

#include "DBManager.h"

#include <vector>

struct MENU_OPTION {
	std::string label;
	User::ACCESS_LEVEL requiredAccessLevel;
};

size_t showMenuOptions(const std::vector<MENU_OPTION> &options, const User &loggedUser);

bool loginMenu(DBManager &db);

void clearConsole();
void toggleEcho();
void printNewlines(unsigned count = 1);
