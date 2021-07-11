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

bool DBManager::updateByID(const Project &project)
{
	try {
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			UPDATE Projects
			SET
				[Name] = ?,
				[Description] = ?,
				LastChangedOn = ?,
				LastChangedBy = ?
			WHERE Id = ?;
		)"));

		const auto &bindTemp0 = project.getName();
		const auto &bindTemp1 = project.getDescription();
		auto bindTemp2 = project.getLastChangedOn();
		auto bindTemp3 = project.getLastChangedBy();
		auto bindTemp4 = project.getID();

		statement.bind(0, bindTemp0.c_str());
		if (bindTemp1.size())
			statement.bind(1, bindTemp1.c_str());
		else
			statement.bind_null(1);
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

bool DBManager::updateByID(const Task &task)
{
	try {
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			UPDATE Tasks
			SET
				ProjectId = ?,
				AssigneeId = ?,
				Title = ?,
				[Description] = ?,
				[Status] = ?,
				LastChangedOn = ?,
				LastChangedBy = ?
			WHERE Id = ?;
		)"));

		auto bindTemp0 = task.getProjectID();
		auto bindTemp1 = task.getAssigneeID();
		const auto &bindTemp2 = task.getTitle();
		const auto &bindTemp3 = task.getDescription();
		auto bindTemp4 = (int)task.getStatus();
		auto bindTemp5 = task.getLastChangedOn();
		auto bindTemp6 = task.getLastChangedBy();
		auto bindTemp7 = task.getID();

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

		statement.execute();
	}
	catch (exception &e) {
		cerr << e.what() << endl;
		return false;
	}

	return true;
}

bool DBManager::updateByID(const Team &team)
{
	try {
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			UPDATE Teams
			SET
				[Name] = ?,
				LastChangedOn = ?,
				LastChangedBy = ?
			WHERE Id = ?;
		)"));

		const auto &bindTemp0 = team.getName();
		auto bindTemp1 = team.getLastChangedOn();
		auto bindTemp2 = team.getLastChangedBy();
		auto bindTemp3 = team.getID();

		statement.bind(0, bindTemp0.c_str());
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

bool DBManager::updateByID(const User &user)
{
	try {
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			UPDATE Users
			SET
				Username = ?,
				FirstName = ?,
				LastName = ?,
				LastChangedOn = ?,
				LastChangedBy = ?,
				AccessLevel = ?
			WHERE
				Id = ?;
		)"));

		const auto &bindTemp0 = user.getUsername();
		const auto &bindTemp1 = user.getFirstName();
		const auto &bindTemp2 = user.getLastName();
		auto bindTemp3 = user.getLastChangedOn();
		auto bindTemp4 = user.getLastChangedBy();
		auto bindTemp5 = (int)user.getAccessLevel();
		auto bindTemp6 = user.getID();

		statement.bind(0, bindTemp0.c_str());
		statement.bind(1, bindTemp1.c_str());
		statement.bind(2, bindTemp2.c_str());
		statement.bind(3, &bindTemp3);
		statement.bind(4, &bindTemp4);
		statement.bind(5, &bindTemp5);
		statement.bind(6, &bindTemp6);

		statement.execute();
	}
	catch (exception &e) {
		cerr << e.what() << endl;
		return false;
	}

	return true;
}

bool DBManager::updateByID(const User &user, const string &password)
{
	try {
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			UPDATE Users
			SET
				Username = ?,
				[Password] = ?,
				FirstName = ?,
				LastName = ?,
				LastChangedOn = ?,
				LastChangedBy = ?,
				AccessLevel = ?
			WHERE
				Id = ?;
		)"));

		const auto &bindTemp0 = user.getUsername();
		const auto &bindTemp2 = user.getFirstName();
		const auto &bindTemp3 = user.getLastName();
		auto bindTemp4 = user.getLastChangedOn();
		auto bindTemp5 = user.getLastChangedBy();
		auto bindTemp6 = (int)user.getAccessLevel();
		auto bindTemp7 = user.getID();

		statement.bind(0, bindTemp0.c_str());
		statement.bind(1, password.c_str());
		statement.bind(2, bindTemp2.c_str());
		statement.bind(3, bindTemp3.c_str());
		statement.bind(4, &bindTemp4);
		statement.bind(5, &bindTemp5);
		statement.bind(6, &bindTemp6);
		statement.bind(7, &bindTemp7);

		statement.execute();
	}
	catch (exception &e) {
		cerr << e.what() << endl;
		return false;
	}

	return true;
}

bool DBManager::deleteByID(const Project &project)
{
	try {
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			UPDATE Projects
			SET
				IsDeleted = 1
			WHERE Id = ?
		)"));

		auto bindTemp0 = project.getID();

		statement.bind(0, &bindTemp0);

		statement.execute();
	}
	catch (exception &e) {
		cerr << e.what() << endl;
		return false;
	}

	return true;
}

bool DBManager::deleteByID(const Task &task)
{
	try {
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			UPDATE Tasks
			SET
				IsDeleted = 1
			WHERE Id = ?
		)"));

		auto bindTemp0 = task.getID();

		statement.bind(0, &bindTemp0);

		statement.execute();
	}
	catch (exception &e) {
		cerr << e.what() << endl;
		return false;
	}

	return true;
}

bool DBManager::deleteByID(const Team &team)
{
	try {
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			UPDATE Teams
			SET
				IsDeleted = 1
			WHERE Id = ?
		)"));

		auto bindTemp0 = team.getID();

		statement.bind(0, &bindTemp0);

		statement.execute();
	}
	catch (exception &e) {
		cerr << e.what() << endl;
		return false;
	}

	return true;
}

bool DBManager::deleteByID(const User &user)
{
	try {
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			UPDATE Users
			SET
				IsDeleted = 1
			WHERE Id = ?
		)"));

		auto bindTemp0 = user.getID();

		statement.bind(0, &bindTemp0);

		statement.execute();
	}
	catch (exception &e) {
		cerr << e.what() << endl;
		return false;
	}

	return true;
}

bool DBManager::deleteByID(const WorkLog &workLog)
{
	try {
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			UPDATE WorkLogs
			SET
				IsDeleted = 1
			WHERE Id = ?
		)"));

		auto bindTemp0 = workLog.getID();

		statement.bind(0, &bindTemp0);

		statement.execute();
	}
	catch (exception &e) {
		cerr << e.what() << endl;
		return false;
	}

	return true;
}

Project DBManager::getByID(Project &project, int32_t id)
{
	try {
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			SELECT
				Id,
				[Name],
				CreatedOn,
				CreatedBy,
				LastChangedOn,
				LastChangedBy,
				[Description]
			FROM Projects
			WHERE Id = ?;
		)"));

		statement.bind(0, &id);

		auto resSet = statement.execute();
		if (!resSet.next()) return project;

		auto id = resSet.get<int32_t>(0);
		const auto &name = resSet.get<string>(1);
		auto createdOn = resSet.get<nanodbc::timestamp>(2);
		auto createdBy = resSet.get<int32_t>(3);
		auto lastChangedOn = resSet.get<nanodbc::timestamp>(4);
		auto lastChangedBy = resSet.get<int32_t>(5);
		const auto &description = resSet.get<string>(6, "");

		Project out(*this, id, name, description, createdOn, createdBy, lastChangedOn, lastChangedBy);

		return out;
	}
	catch (exception &e) {
		cerr << e.what() << endl;
		return project;
	}
}

Task DBManager::getByID(Task &task, int32_t id)
{
	try {
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			SELECT
				Id,
				ProjectId,
				AssigneeId,
				Title,
				[Status],
				CreatedOn,
				CreatedBy,
				LastChangedOn,
				LastChangedBy,
				[Description]
			FROM Tasks
			WHERE Id = ?;
		)"));

		statement.bind(0, &id);

		auto resSet = statement.execute();
		if (!resSet.next()) return task;

		auto id = resSet.get<int32_t>(0);
		auto projectID = resSet.get<int32_t>(1);
		auto assigneeID = resSet.get<int32_t>(2);
		const auto &title = resSet.get<string>(3);
		Task::STATUS status = (Task::STATUS)resSet.get<int>(4);
		auto createdOn = resSet.get<nanodbc::timestamp>(5);
		auto createdBy = resSet.get<int32_t>(6);
		auto lastChangedOn = resSet.get<nanodbc::timestamp>(7);
		auto lastChangedBy = resSet.get<int32_t>(8);
		const auto &description = resSet.get<string>(9, "");

		Task out(*this,
				 id,
				 projectID,
				 assigneeID,
				 title,
				 description,
				 status,
				 createdOn,
				 createdBy,
				 lastChangedOn,
				 lastChangedBy);

		return out;
	}
	catch (exception &e) {
		cerr << e.what() << endl;
		return task;
	}
}

Team DBManager::getByID(Team &team, int32_t id)
{
	try {
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			SELECT
				Id,
				[Name],
				CreatedOn,
				CreatedBy,
				LastChangedOn,
				LastChangedBy
			FROM Teams
			WHERE Id = ?;
		)"));

		statement.bind(0, &id);

		auto resSet = statement.execute();
		if (!resSet.next()) return team;

		auto id = resSet.get<int32_t>(0);
		const auto &name = resSet.get<string>(1);
		auto createdOn = resSet.get<nanodbc::timestamp>(2);
		auto createdBy = resSet.get<int32_t>(3);
		auto lastChangedOn = resSet.get<nanodbc::timestamp>(4);
		auto lastChangedBy = resSet.get<int32_t>(5);

		return {*this, id, name, createdOn, createdBy, lastChangedOn, lastChangedBy};
	}
	catch (exception &e) {
		cerr << e.what() << endl;
		return team;
	}
}

User DBManager::getByID(User &user, int32_t id)
{
	try {
		nanodbc::statement statement(connection);

		nanodbc::prepare(statement, NANODBC_TEXT(R"(
			SELECT
				Username,
				FirstName,
				LastName,
				CreatedOn,
				CreatedBy,
				LastChangedOn,
				LastChangedBy,
				AccessLevel
			FROM Users
			WHERE Id = ?;
		)"));

		statement.bind(0, &id);

		auto resSet = statement.execute();
		if (!resSet.next()) return user;

		const auto &username = resSet.get<string>(0);
		const auto &firstName = resSet.get<string>(1);
		const auto &lastName = resSet.get<string>(2);
		auto createdOn = resSet.get<nanodbc::timestamp>(3);
		auto createdBy = resSet.get<int32_t>(4);
		auto lastChangedOn = resSet.get<nanodbc::timestamp>(5);
		auto lastChangedBy = resSet.get<int32_t>(6);
		auto accessLevel = (User::ACCESS_LEVEL)resSet.get<int>(7);

		return {
			*this, id, username, firstName, lastName, createdOn, createdBy, lastChangedOn, lastChangedBy, accessLevel};
	}
	catch (exception &e) {
		cerr << e.what() << endl;
		return user;
	}
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
