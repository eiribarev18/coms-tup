#include "console_io.h"

#include <cstring>
#include <iostream>

using namespace std;

void getUnsignedNumber(size_t &x, size_t maxValue = -1, size_t minValue = 0, char delimiter = '\n')
{
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

	x = stoull(raw);
}

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

	return false;
}
