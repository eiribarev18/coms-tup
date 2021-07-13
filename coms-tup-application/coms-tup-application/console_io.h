#pragma once

#include "DBManager.h"

#include <vector>

struct MENU_OPTION {
	std::string label;
	User::ACCESS_LEVEL requiredAccessLevel;
};

size_t showMenuOptions(const std::vector<MENU_OPTION> &options, const User &loggedUser);
size_t getMenuOptionChoice(const std::vector<MENU_OPTION> &options, const User &loggedUser);

bool loginMenu(DBManager &db);

bool mainMenu(DBManager &db, User &loggedUser, bool &showLogin);

void clearConsole();
void toggleEcho();
void printNewlines(unsigned count = 1);
