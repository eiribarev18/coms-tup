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
				([Name], [Description], CreatedOn, CreatedBy, LastChangedOn, LastChangedBy)
			VALUES
				(?, ?, ?, ?, ?, ?);
		)"));

		const auto &bindTemp0 = project.getName();
		const auto &bindTemp1 = project.getDescription();
		auto bindTemp2 = project.getCreatedOn();
		auto bindTemp3 = project.getCreatedBy();
		auto bindTemp4 = project.getLastChangedOn();
		auto bindTemp5 = project.getLastChangedBy();

		statement.bind(0, bindTemp0.c_str());
		if (bindTemp1.size())
			statement.bind(1, bindTemp1.c_str());
		else
			statement.bind_null(1);
		statement.bind(2, &bindTemp2);
		statement.bind(3, &bindTemp3);
		statement.bind(4, &bindTemp4);
		statement.bind(5, &bindTemp5);

		statement.execute();
	}
	catch (exception &e) {
		cerr << e.what() << endl;
		return false;
	}

	return true;
}

bool DBManager::insert(const Task &task)
{
	try {
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			INSERT INTO Tasks
				(ProjectId, AssigneeId, Title, [Description], [Status], CreatedOn, CreatedBy, LastChangedOn, LastChangedBy)
			VALUES
				(?, ?, ?, ?, ?, ?, ?, ?, ?);
		)"));

		auto bindTemp0 = task.getProjectID();
		auto bindTemp1 = task.getAssigneeID();
		const auto &bindTemp2 = task.getTitle();
		const auto &bindTemp3 = task.getDescription();
		auto bindTemp4 = (int)task.getStatus();
		auto bindTemp5 = task.getCreatedOn();
		auto bindTemp6 = task.getCreatedBy();
		auto bindTemp7 = task.getLastChangedOn();
		auto bindTemp8 = task.getLastChangedBy();

		statement.bind(0, &bindTemp0);
		statement.bind(1, &bindTemp1);
		statement.bind(2, bindTemp2.c_str());
		if (bindTemp3.size())
			statement.bind(3, bindTemp3.c_str());
		else
			statement.bind_null(3);
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

bool DBManager::insert(const Team &team)
{
	try {
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			INSERT INTO Teams
				([Name], CreatedOn, CreatedBy, LastChangedOn, LastChangedBy)
			VALUES
				(?, ?, ?, ?, ?);
		)"));

		const auto &bindTemp0 = team.getName();
		auto bindTemp1 = team.getCreatedOn();
		auto bindTemp2 = team.getCreatedBy();
		auto bindTemp3 = team.getLastChangedOn();
		auto bindTemp4 = team.getLastChangedBy();

		statement.bind(0, bindTemp0.c_str());
		statement.bind(1, &bindTemp1);
		statement.bind(2, &bindTemp2);
		statement.bind(3, &bindTemp3);
		statement.bind(4, &bindTemp4);

		statement.execute();
	}
	catch (exception &e) {
		cerr << e.what() << endl;
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
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			INSERT INTO WorkLogs
				(TaskId, UserId, [Date], HoursSpent)
			VALUES
				(?, ?, ?, ?);
		)"));

		auto bindTemp0 = workLog.getTaskID();
		auto bindTemp1 = workLog.getUserID();
		auto bindTemp2 = workLog.getDate();
		auto bindTemp3 = (int)workLog.getHoursSpent();

		statement.bind(0, &bindTemp0);
		statement.bind(1, &bindTemp1);
		statement.bind(2, &bindTemp2);
		statement.bind(3, &bindTemp3);

		statement.execute();
	}
	catch (exception &e) {
		cerr << e.what() << endl;
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
