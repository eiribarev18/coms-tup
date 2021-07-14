#include "console_io.h"

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
			break;
		case 3:
			break;
		case 4:
			return false;
	}

	return true;
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
