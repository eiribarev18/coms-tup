#include "DBManager.h"

#include "utils.h"

#include <iostream>

using namespace std;

DBManager::DBManager(const string &connectionString)
{
	connection.connect(connectionString);
}

bool DBManager::insert(const Project &project)
{
	try {
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			INSERT INTO Projects
				(
		)"));
	}
	catch (exception &e) {
		return false;
	}

	return true;
}

bool DBManager::insert(const Task &task)
{
	try {
	}
	catch (exception &e) {
		return false;
	}

	return true;
}

bool DBManager::insert(const Team &team)
{
	try {
	}
	catch (exception &e) {
		return false;
	}

	return true;
}

bool DBManager::insert(const User &user, const string &password)
{
	try {
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			INSERT INTO Users
				(Username, [Password], FirstName, LastName, CreatedOn, CreatedBy, LastChangedOn, LastChangedBy, AccessLevel)
			VALUES
				(?, ?, ?, ?, ?, ?, ?, ?, ?);
		)"));

		const auto &bindTemp0 = user.getUsername();
		const auto &bindTemp2 = user.getFirstName();
		const auto &bindTemp3 = user.getLastName();
		auto bindTemp4 = user.getCreatedOn();
		auto bindTemp5 = user.getCreatedBy();
		auto bindTemp6 = user.getLastChangedOn();
		auto bindTemp7 = user.getLastChangedBy();
		auto bindTemp8 = (int)user.getAccessLevel();

		statement.bind(0, bindTemp0.c_str());
		statement.bind(1, password.c_str());
		statement.bind(2, bindTemp2.c_str());
		statement.bind(3, bindTemp3.c_str());
		statement.bind(4, &bindTemp4);
		statement.bind(5, &bindTemp5);
		statement.bind(6, &bindTemp6);
		statement.bind(7, &bindTemp7);
		statement.bind(8, &bindTemp8);

		statement.execute();
	}
	catch (exception &e) {
		cerr << e.what() << endl;
		return false;
	}

	return true;
}

bool DBManager::insert(const WorkLog &workLog)
{
	try {
	}
	catch (exception &e) {
		return false;
	}

	return true;
}

nanodbc::timestamp DBManager::getDate(bool includeTime)
{
	nanodbc::statement statement(connection);

	nanodbc::prepare(statement, NANODBC_TEXT(R"(
		SELECT GETUTCDATE();
	)"));

	auto resSet = statement.execute();
	resSet.next();

	auto ts = resSet.get<nanodbc::timestamp>(0);

	if (!includeTime) {
		ts.hour = 0;
		ts.min = 0;
		ts.sec = 0;
	}
	ts.fract = 0;

	return ts;
}