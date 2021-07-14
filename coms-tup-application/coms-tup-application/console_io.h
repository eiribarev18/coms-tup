#pragma once

#include "DBManager.h"
#include "listTable.h"

#include <vector>

struct MENU_OPTION {
	std::string label;
	User::ACCESS_LEVEL requiredAccessLevel;
};

size_t showMenuOptions(const std::vector<MENU_OPTION> &options, const User &loggedUser);
size_t getMenuOptionChoice(size_t maxChoice);
size_t getMenuOptionChoice(const std::vector<MENU_OPTION> &options, const User &loggedUser);

bool loginMenu(DBManager &db);

bool mainMenu(DBManager &db, User &loggedUser, bool &showLogin);

bool userManagementMenu(DBManager &db, User &loggedUser);

void createUserMenu(DBManager &db, User &loggedUser);

void clearConsole();
void toggleEcho();
void printNewlines(unsigned count = 1);
