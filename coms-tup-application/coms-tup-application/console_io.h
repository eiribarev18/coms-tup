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

bool projectManagementMenu(DBManager &db, User &loggedUser);
bool teamManagementMenu(DBManager &db, User &loggedUser);
bool userManagementMenu(DBManager &db, User &loggedUser);

void createProjectMenu(DBManager &db, User &loggedUser);
void deleteProjectMenu(DBManager &db, User &loggedUser);
void chooseProjectToEditMenu(DBManager &db, User &loggedUser);

bool editProjectMenu(DBManager &db, User &loggedUser, Project &projectToEdit);

void editProjectNameMenu(DBManager &db, User &loggedUser, Project &projectToEdit);
void editProjectDescriptionMenu(DBManager &db, User &loggedUser, Project &projectToEdit);

void createTeamMenu(DBManager &db, User &loggedUser);
void deleteTeamMenu(DBManager &db);
void chooseTeamToEditMenu(DBManager &db, User &loggedUser);

bool editTeamMenu(DBManager &db, User &loggedUser, Team &teamToEdit);

void editTeamNameMenu(DBManager &db, User &loggedUser, Team &teamToEdit);
void assignTeamMemberMenu(DBManager &db, User &loggedUser, Team &teamToEdit);
void dismissTeamMemberMenu(DBManager &db, User &loggedUser, Team &teamToEdit);

void createUserMenu(DBManager &db, User &loggedUser);
void deleteUserMenu(DBManager &db);
void editUserMenu(DBManager &db, User &loggeduser);

void clearConsole();
void toggleEcho();
void printNewlines(unsigned count = 1);

template <typename T>
void getUnsignedNumber(T &x, size_t maxValue = -1, size_t minValue = 0, char delimiter = '\n')
{
	using namespace std;

	std::string raw;

	getline(cin, raw, delimiter);

	for (size_t i = 0; i < raw.size(); i++) {
		if (raw[i] < '0' or raw[i] > '9') throw runtime_error("Non-digit character encountered");
	}

	if (stoull(raw) > maxValue) {
		throw out_of_range("Number " + to_string((unsigned long long)x) +
						   " is larger than maxValue=" + to_string(maxValue));
	}
	if (stoull(raw) < minValue) {
		throw out_of_range("Number " + to_string((unsigned long long)x) +
						   " is smaller than minValue=" + to_string(maxValue));
	}

	x = (T)stoull(raw);
}
