#include "console_io.h"

#include "utils.h"

#include <algorithm>
#include <cstring>
#include <iostream>

using namespace std;

size_t showMenuOptions(const std::vector<MENU_OPTION> &options, const User &loggedUser)
{
	size_t num = 1;

	for (auto option : options) {
		if (option.requiredAccessLevel <= loggedUser.getAccessLevel()) {
			cout << num << ". " << option.label << endl;
			num++;
		}
	}

	return --num;
}

size_t getMenuOptionChoice(size_t maxChoice)
{
	size_t choice;

	while (true) {
		cout << "Enter choice (1 - " << maxChoice << "): ";
		try {
			getUnsignedNumber(choice, maxChoice, 1);
		}
		catch (...) {
			cout << "Invalid input!" << endl;
			continue;
		}
		break;
	}

	return choice;
}

size_t getMenuOptionChoice(const std::vector<MENU_OPTION> &options, const User &loggedUser)
{
	size_t numberOfValidOptions = count_if(options.begin(), options.end(), [loggedUser](const MENU_OPTION &option) {
		return option.requiredAccessLevel <= loggedUser.getAccessLevel();
	});

	size_t choice = getMenuOptionChoice(numberOfValidOptions);

	for (size_t i = 0, temp = choice; temp; i++, temp--) {
		if (options[i].requiredAccessLevel > loggedUser.getAccessLevel()) {
			choice++;
			temp++;
		}
	}

	return choice - 1;
}

bool loginMenu(DBManager &db)
{
	string username, password;
	int32_t id;

	cout << "Username: ";
	getline(cin, username);

	cout << "Password: ";
	toggleEcho();
	getline(cin, password);
	toggleEcho();
	cout << endl;

	clearConsole();

	try {
		id = db.getIDWithCredentials(username, password);
	}
	catch (runtime_error &e) {
		if (!strcmp(e.what(), "No user with matching username and password exists")) {
			cout << e.what();
			printNewlines(2);

			return true;
		}

		throw e;
	}

	User loggedUser = db.getByID(loggedUser, id);
	bool showAgain = false;

	while (mainMenu(db, loggedUser, showAgain)) {};

	return showAgain;
}

bool mainMenu(DBManager &db, User &loggedUser, bool &showLogin)
{
	cout << "Logged in as: " << loggedUser.getUsername() << " - " << loggedUser.getFirstName() << " "
		 << loggedUser.getLastName() << " (" << to_string(loggedUser.getAccessLevel()) << ")" << endl;
	printNewlines();

	vector<MENU_OPTION> options = {{"User Management", User::ACCESS_LEVEL::USER},
								   {"Team Management", User::ACCESS_LEVEL::USER},
								   {"Project Management", User::ACCESS_LEVEL::USER},
								   {"Task Management", User::ACCESS_LEVEL::USER},
								   {"Work Log Management", User::ACCESS_LEVEL::USER},
								   {"Log out", User::ACCESS_LEVEL::USER},
								   {"Exit program", User::ACCESS_LEVEL::USER}};

	showMenuOptions(options, loggedUser);

	size_t chosenOptionIndex = getMenuOptionChoice(options, loggedUser);

	clearConsole();

	switch (chosenOptionIndex) {
		case 0:
			while (userManagementMenu(db, loggedUser)) {};
			break;
		case 1:
			while (teamManagementMenu(db, loggedUser)) {};
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			showLogin = true;
		case 6:
			clearConsole();
			return false;
	}

	clearConsole();

	return true;
}

bool teamManagementMenu(DBManager &db, User &loggedUser)
{
	vector<MENU_OPTION> options = {{"List teams", User::ACCESS_LEVEL::USER},
								   {"Create team", User::ACCESS_LEVEL::ADMIN},
								   {"Edit team", User::ACCESS_LEVEL::ADMIN},
								   {"Delete team", User::ACCESS_LEVEL::ADMIN},
								   {"Back", User::ACCESS_LEVEL::USER}};

	showMenuOptions(options, loggedUser);

	size_t chosenOptionIndex = getMenuOptionChoice(options, loggedUser);

	clearConsole();

	switch (chosenOptionIndex) {
		case 0:
			listTable<Team>(bind(&DBManager::getAllTeams, &db));
			printNewlines();
			break;
		case 1:
			createTeamMenu(db, loggedUser);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			return false;
	}

	return true;
}

bool userManagementMenu(DBManager &db, User &loggedUser)
{
	vector<MENU_OPTION> options = {{"List users", User::ACCESS_LEVEL::USER},
								   {"Create user", User::ACCESS_LEVEL::ADMIN},
								   {"Edit user", User::ACCESS_LEVEL::ADMIN},
								   {"Delete user", User::ACCESS_LEVEL::ADMIN},
								   {"Back", User::ACCESS_LEVEL::USER}};

	showMenuOptions(options, loggedUser);

	size_t chosenOptionIndex = getMenuOptionChoice(options, loggedUser);

	clearConsole();

	switch (chosenOptionIndex) {
		case 0:
			listTable<User>(bind(&DBManager::getAllUsers, &db));
			printNewlines();
			break;
		case 1:
			createUserMenu(db, loggedUser);
			break;
		case 2:
			editUserMenu(db, loggedUser);
			break;
		case 3:
			deleteUserMenu(db);
			break;
		case 4:
			return false;
	}

	return true;
}

void createTeamMenu(DBManager &db, User &loggedUser)
{
	Team newTeam(loggedUser.getID(), db);
	string temp;

	cout << "--- New Team ---" << endl;
	printNewlines();

	cout << "Name: ";
	getline(cin, temp);
	newTeam.setName(temp, loggedUser.getID());

	clearConsole();

	if (db.insert(newTeam))
		cout << "Team successfully added!" << endl;
	else
		cout << "Failed to add team" << endl;

	printNewlines();
}

void createUserMenu(DBManager &db, User &loggedUser)
{
	User newUser(loggedUser.getID(), db);
	string temp;

	cout << "--- New User ---" << endl;
	printNewlines();

	cout << "Username: ";
	getline(cin, temp);
	newUser.setUsername(temp, loggedUser.getID());

	cout << "First name: ";
	getline(cin, temp);
	newUser.setFirstName(temp, loggedUser.getID());

	cout << "Surname: ";
	getline(cin, temp);
	newUser.setLastName(temp, loggedUser.getID());

	cout << "Password: ";
	toggleEcho();
	getline(cin, temp);
	toggleEcho();
	printNewlines();

	clearConsole();

	if (db.insert(newUser, temp))
		cout << "User successfully added!" << endl;
	else
		cout << "Failed to add user" << endl;

	printNewlines();
}

void deleteUserMenu(DBManager &db)
{
	auto users = db.getAllUsers();
	int32_t choice;

	listTable(users);
	printNewlines();

	while (true) {
		cout << "Choose user to delete (by the ID column): ";
		try {
			getUnsignedNumber(choice);
		}
		catch (...) {
			cout << "Invalid input!" << endl;
			continue;
		}
		break;
	}

	clearConsole();

	if (users.find(choice) == users.end()) {
		cout << "No user with ID " << choice << " exists" << endl;
		printNewlines();

		return;
	}

	if (db.deleteByID(users.at(choice)))
		cout << "User deleted successfully!" << endl;
	else
		cout << "Could not delete user" << endl;

	printNewlines();
}

void editUserMenu(DBManager &db, User &loggedUser)
{
	auto users = db.getAllUsers();
	int32_t choice;

	listTable(users);
	printNewlines();

	while (true) {
		cout << "Choose user to edit (by the ID column): ";
		try {
			getUnsignedNumber(choice);
		}
		catch (...) {
			cout << "Invalid input!" << endl;
			continue;
		}
		break;
	}

	clearConsole();

	if (users.find(choice) == users.end()) {
		cout << "No user with ID " << choice << " exists" << endl;
		printNewlines();

		return;
	}

	User userToEdit = users.at(choice);
	string temp, newPassword;

	cout << "--- Edit user " << userToEdit.getUsername() << " ---" << endl;
	printNewlines();
	cout << "After each prompt the current value will be shown in parenthesis.\n"
		 << "Leave empty if you don't wish to change it." << endl;
	printNewlines();

	cout << "Username (" << userToEdit.getUsername() << "): ";
	getline(cin, temp);
	if (temp.size()) userToEdit.setUsername(temp, loggedUser.getID());

	cout << "Password (NOT SHOWN): ";
	toggleEcho();
	getline(cin, newPassword);
	toggleEcho();
	cout << endl;

	cout << "Name (" << userToEdit.getFirstName() << "): ";
	getline(cin, temp);
	if (temp.size()) userToEdit.setFirstName(temp, loggedUser.getID());

	cout << "Surname (" << userToEdit.getLastName() << "): ";
	getline(cin, temp);
	if (temp.size()) userToEdit.setLastName(temp, loggedUser.getID());

	clearConsole();

	if (newPassword.size()) {
		if (db.updateByID(userToEdit, newPassword)) {
			cout << "User updated successfully!" << endl;
			return;
		}
		cout << "Could not update user" << endl;
	}
	if (db.updateByID(userToEdit)) {
		cout << "User updated successfully!" << endl;
		return;
	}
	cout << "Could not update user" << endl;
}
