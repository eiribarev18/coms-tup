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
			while (projectManagementMenu(db, loggedUser)) {};
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

bool projectManagementMenu(DBManager &db, User &loggedUser)
{
	vector<MENU_OPTION> options = {{"List all projects", User::ACCESS_LEVEL::USER},
								   {"List projects assigned to me", User::ACCESS_LEVEL::USER},
								   {"Create project", User::ACCESS_LEVEL::USER},
								   {"Select project", User::ACCESS_LEVEL::USER},
								   {"Delete project", User::ACCESS_LEVEL::USER},
								   {"Back", User::ACCESS_LEVEL::USER}};

	showMenuOptions(options, loggedUser);

	size_t chosenOptionIndex = getMenuOptionChoice(options, loggedUser);

	clearConsole();

	switch (chosenOptionIndex) {
		case 0:
			listTable<Project>(bind(&DBManager::getAllProjects, &db));
			printNewlines();
			break;
		case 1:
			listTable<Project>(bind(&DBManager::getProjectsAssignedToUser, &db, loggedUser));
			printNewlines();
			break;
		case 2:
			createProjectMenu(db, loggedUser);
			break;
		case 3:
			chooseProjectToEditMenu(db, loggedUser);
			break;
		case 4:
			deleteProjectMenu(db, loggedUser);
			break;
		case 5:
			return false;
	}

	return true;
}

bool teamManagementMenu(DBManager &db, User &loggedUser)
{
	vector<MENU_OPTION> options = {{"List teams", User::ACCESS_LEVEL::USER},
								   {"Create team", User::ACCESS_LEVEL::ADMIN},
								   {"Select team", User::ACCESS_LEVEL::USER},
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
			chooseTeamToEditMenu(db, loggedUser);
			break;
		case 3:
			deleteTeamMenu(db);
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

void createProjectMenu(DBManager &db, User &loggedUser)
{
	Project newProject(loggedUser.getID(), db);
	string temp;

	cout << "--- New project ---" << endl;
	printNewlines();

	cout << "Name: ";
	getline(cin, temp);
	newProject.setName(temp, loggedUser.getID());

	cout << "Description: ";
	getline(cin, temp);
	newProject.setDescription(temp, loggedUser.getID());

	clearConsole();

	if (db.insert(newProject))
		cout << "Project successfully added!" << endl;
	else
		cout << "Failed to add project" << endl;

	printNewlines();
}

void deleteProjectMenu(DBManager &db, User &loggedUser)
{
	auto projects = db.getAllProjects();
	int32_t choice;

	if (loggedUser.getAccessLevel() < User::ACCESS_LEVEL::ADMIN) {
		for (auto it = projects.begin(); it != projects.end();) {
			if (it->second.getCreatedBy() != loggedUser.getID())
				it = projects.erase(it);
			else
				it++;
		}
	}

	listTable(projects);
	printNewlines();

	while (true) {
		cout << "Choose project to delete (by the ID column): ";
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

	if (projects.find(choice) == projects.end()) {
		cout << "Cannot delete project with ID " << choice << ".\n"
			 << "It doesn't exist or you don't have permission to perform this action" << endl;
		printNewlines();

		return;
	}

	if (db.deleteByID(projects.at(choice)))
		cout << "Project deleted successfully!" << endl;
	else
		cout << "Could not delete project" << endl;

	printNewlines();
}

void chooseProjectToEditMenu(DBManager &db, User &loggedUser)
{
	auto projects = db.getAllProjects();
	int32_t choice;

	listTable(projects);
	printNewlines();

	while (true) {
		cout << "Choose project to select (by the ID column): ";
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

	if (projects.find(choice) == projects.end()) {
		cout << "No project with ID " << choice << " exists" << endl;
		printNewlines();

		return;
	}

	Project projectToEdit = projects.at(choice);

	while (editProjectMenu(db, loggedUser, projectToEdit)) {};
}

bool editProjectMenu(DBManager &db, User &loggedUser, Project &projectToEdit)
{
	const bool doesNotOwnProject = loggedUser.getID() != projectToEdit.getCreatedBy();

	cout << "--- Edit project " << projectToEdit.getName() << " ---" << endl;
	printNewlines();

	vector<MENU_OPTION> options = {
		{"Edit name", doesNotOwnProject ? User::ACCESS_LEVEL::ADMIN : User::ACCESS_LEVEL::USER},
		{"Edit description", doesNotOwnProject ? User::ACCESS_LEVEL::ADMIN : User::ACCESS_LEVEL::USER},
		{"List assigned teams", User::ACCESS_LEVEL::USER},
		{"Assign team", doesNotOwnProject ? User::ACCESS_LEVEL::ADMIN : User::ACCESS_LEVEL::USER},
		{"Dismiss team", doesNotOwnProject ? User::ACCESS_LEVEL::ADMIN : User::ACCESS_LEVEL::USER},
		{"Back", User::ACCESS_LEVEL::USER}};

	showMenuOptions(options, loggedUser);

	size_t chosenOptionIndex = getMenuOptionChoice(options, loggedUser);

	clearConsole();

	switch (chosenOptionIndex) {
		case 0:
			editProjectNameMenu(db, loggedUser, projectToEdit);
			break;
		case 1:
			editProjectDescriptionMenu(db, loggedUser, projectToEdit);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			return false;
	}

	return true;
}

void editProjectNameMenu(DBManager &db, User &loggedUser, Project &projectToEdit)
{
	string temp;

	cout << "After the prompt the current value will be shown in parenthesis.\n"
		 << "Leave empty if you don't wish to change it." << endl;
	printNewlines();

	cout << "Name (" << projectToEdit.getName() << "): ";
	getline(cin, temp);
	if (temp.size()) projectToEdit.setName(temp, loggedUser.getID());

	clearConsole();
}

void editProjectDescriptionMenu(DBManager &db, User &loggedUser, Project &projectToEdit)
{
	string temp;

	cout << "After the prompt the current value will be shown in parenthesis.\n"
		 << "Leave empty if you wish to unset it." << endl;
	printNewlines();

	cout << "Description (" << projectToEdit.getDescription() << "): ";
	getline(cin, temp);
	projectToEdit.setDescription(temp, loggedUser.getID());

	clearConsole();
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

void deleteTeamMenu(DBManager &db)
{
	auto teams = db.getAllTeams();
	int32_t choice;

	listTable(teams);
	printNewlines();

	while (true) {
		cout << "Choose team to delete (by the ID column): ";
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

	if (teams.find(choice) == teams.end()) {
		cout << "No team with ID " << choice << " exists" << endl;
		printNewlines();

		return;
	}

	if (db.deleteByID(teams.at(choice)))
		cout << "Team deleted successfully!" << endl;
	else
		cout << "Could not delete team" << endl;

	printNewlines();
}

void chooseTeamToEditMenu(DBManager &db, User &loggedUser)
{
	auto teams = db.getAllTeams();
	int32_t choice;

	listTable(teams);
	printNewlines();

	while (true) {
		cout << "Choose team to select (by the ID column): ";
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

	if (teams.find(choice) == teams.end()) {
		cout << "No team with ID " << choice << " exists" << endl;
		printNewlines();

		return;
	}

	Team teamToEdit = teams.at(choice);

	while (editTeamMenu(db, loggedUser, teamToEdit)) {};
}

bool editTeamMenu(DBManager &db, User &loggedUser, Team &teamToEdit)
{
	cout << "--- Edit team " << teamToEdit.getName() << " ---" << endl;
	printNewlines();

	vector<MENU_OPTION> options = {{"Edit name", User::ACCESS_LEVEL::ADMIN},
								   {"List members", User::ACCESS_LEVEL::USER},
								   {"Assign member", User::ACCESS_LEVEL::ADMIN},
								   {"Remove member", User::ACCESS_LEVEL::ADMIN},
								   {"Back", User::ACCESS_LEVEL::USER}};

	showMenuOptions(options, loggedUser);

	size_t chosenOptionIndex = getMenuOptionChoice(options, loggedUser);

	clearConsole();

	switch (chosenOptionIndex) {
		case 0:
			editTeamNameMenu(db, loggedUser, teamToEdit);
			break;
		case 1:
			listTable<User>(bind(&DBManager::getMembersOfTeam, &db, teamToEdit));
			printNewlines();
			break;
		case 2:
			assignTeamMemberMenu(db, loggedUser, teamToEdit);
			break;
		case 3:
			dismissTeamMemberMenu(db, loggedUser, teamToEdit);
			break;
		case 4:
			return false;
	}

	return true;
}

void editTeamNameMenu(DBManager &db, User &loggedUser, Team &teamToEdit)
{
	string temp;

	cout << "After the prompt the current value will be shown in parenthesis.\n"
		 << "Leave empty if you don't wish to change it." << endl;
	printNewlines();

	cout << "Name (" << teamToEdit.getName() << "): ";
	getline(cin, temp);
	if (temp.size()) teamToEdit.setName(temp, loggedUser.getID());

	clearConsole();
}

void assignTeamMemberMenu(DBManager &db, User &loggedUser, Team &teamToEdit)
{
	auto users = db.getAllUsers();
	int32_t choice;

	listTable(users);
	printNewlines();

	while (true) {
		cout << "Choose user to assign (by the ID column): ";
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

	if (db.assignTeamMember(teamToEdit, users.at(choice)))
		cout << "User assigned successfully!" << endl;
	else
		cout << "Could not assign user" << endl;

	printNewlines();
}

void dismissTeamMemberMenu(DBManager &db, User &loggedUser, Team &teamToEdit)
{
	auto users = db.getMembersOfTeam(teamToEdit);
	int32_t choice;

	listTable(users);
	printNewlines();

	while (true) {
		cout << "Choose user to assign (by the ID column): ";
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

	if (db.dismissTeamMember(teamToEdit, users.at(choice)))
		cout << "User dismissed successfully!" << endl;
	else
		cout << "Could not dismiss user" << endl;

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
