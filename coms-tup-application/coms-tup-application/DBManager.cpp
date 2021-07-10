#include "DBManager.h"

#include "utils.h"

using namespace std;

DBManager::DBManager(const string &connectionString)
{
	connection.connect(connectionString);
}

std::string DBManager::getDate(bool includeTime)
{
	nanodbc::statement statement(connection);

	nanodbc::prepare(statement, NANODBC_TEXT(R"(
		SELECT GETUTCDATE();
	)"));

	auto resSet = statement.execute();
	resSet.next();

	auto ts = resSet.get<nanodbc::timestamp>(0);

	return to_string(ts, includeTime);
}
