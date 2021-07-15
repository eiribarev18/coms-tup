#pragma once

#include "DBManager.h"
#include "listTable.h"

#include <vector>

/**
 * @file console_io.h
 *
 * @brief Console input/output functions.
 */

/**
 * @brief A struct representing an option in a menu.
 */
struct MENU_OPTION {
	/**
	 * @brief The text to display on the actual menu.
	 */
	std::string label;
	/**
	 * @brief The minimal access level a user should have in order to select this option.
	 */
	User::ACCESS_LEVEL requiredAccessLevel;
};

/**
 * @brief Displays all appropriate menu options.
 *
 * Displays only the menu options with @c requiredAccessLevel less than or equal to the user's access level.
 *
 * @param options A std::vector of #MENU_OPTION with all the options in the menu.
 * @param loggedUser The currently logged in user.
 *
 * @return The number of displayed options.
 */
size_t showMenuOptions(const std::vector<MENU_OPTION> &options, const User &loggedUser);
/**
 * @brief Simple function for getting a number between 1 and @p maxChoice.
 *
 * Prompts for a number and repeats until a valid number between 1 and @p maxChoice is entered.
 *
 * @param maxChoice The maximum value accepted.
 *
 * @return The value chosen by the user.
 */
size_t getMenuOptionChoice(size_t maxChoice);
/**
 * @brief Smart function for choosing a menu option.
 *
 * Prompts for a number between 1 and the number of options @p loggedUser has access to using
 * getMenuOptionChoice(size_t) and calculates the index of the chosen option in @p options.
 *
 * @param options A std::vector of #MENU_OPTION with all the options in the menu.
 * @param loggedUser The currently logged in user.
 *
 * @return The index of the item in @p options that the user has chosen.
 *
 * @see showMenuOptions()
 */
size_t getMenuOptionChoice(const std::vector<MENU_OPTION> &options, const User &loggedUser);

/**
 * @brief Displays and handles the choice to the login menu.
 *
 * @param db The DBManager instance to pass to all functions needing it.
 *
 * @return True if the menu should be displayed again, false otherwise.
 */
bool loginMenu(DBManager &db);

/**
 * @brief Displays and handles the choice to the main menu.
 *
 * @param db The DBManager instance to pass to all functions needing it.
 * @param loggedUser The currently logged in user.
 * @param[out] showLogin used by loginMenu() to determine whether it needs to be displayed again.
 *
 * @return True if the menu should be displayed again, false otherwise.
 */
bool mainMenu(DBManager &db, User &loggedUser, bool &showLogin);

/**
 * @brief Displays and handles the choice to the project management menu.
 *
 * @param db The DBManager instance to pass to all functions needing it.
 * @param loggedUser The currently logged in user.
 *
 * @return True if the menu should be displayed again, false otherwise.
 */
bool projectManagementMenu(DBManager &db, User &loggedUser);
/**
 * @brief Displays and handles the choice to the team management menu.
 *
 * @param db The DBManager instance to pass to all functions needing it.
 * @param loggedUser The currently logged in user.
 *
 * @return True if the menu should be displayed again, false otherwise.
 */
bool teamManagementMenu(DBManager &db, User &loggedUser);
/**
 * @brief Displays and handles the choice to the user management menu.
 *
 * @param db The DBManager instance to pass to all functions needing it.
 * @param loggedUser The currently logged in user.
 *
 * @return True if the menu should be displayed again, false otherwise.
 */
bool userManagementMenu(DBManager &db, User &loggedUser);

/**
 * @brief Menu for creating a project.
 *
 * Prompts the user for the necessary data and creates a project.
 * That project is then inserted into the database using DBManager::insert(const Project &).
 *
 * @param db The DBManager instance to pass to all functions needing it.
 * @param loggedUser The currently logged in user.
 */
void createProjectMenu(DBManager &db, User &loggedUser);
void deleteProjectMenu(DBManager &db, User &loggedUser);
void chooseProjectToEditMenu(DBManager &db, User &loggedUser);

bool editProjectMenu(DBManager &db, User &loggedUser, Project &projectToEdit);

void editProjectNameMenu(DBManager &db, User &loggedUser, Project &projectToEdit);
void editProjectDescriptionMenu(DBManager &db, User &loggedUser, Project &projectToEdit);
void assignTeamMenu(DBManager &db, User &loggedUser, Project &projectToEdit);
void dismissTeamMenu(DBManager &db, User &loggedUser, Project &projectToEdit);

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

/**
 * @brief Clears the console.
 */
void clearConsole();
/**
 * @brief Toggles the console input echo.
 */
void toggleEcho();
/**
 * @brief Prints the specified number of empty lines to the console.
 *
 * @param count The number of empty lines to print.
 */
void printNewlines(unsigned count = 1);

/**
 * @brief Validated unsigned number input.
 *
 * Reads from the standard input until @p delimiter is reached and tries to parse that as an unsigned number of
 * type @p T.
 *
 * @param[out] x The number to get.
 * @param maxValue The maximal allowed value.
 * @param minValue The minimal allowed value.
 * @param delimiter The character at which to stop reading.
 */
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
