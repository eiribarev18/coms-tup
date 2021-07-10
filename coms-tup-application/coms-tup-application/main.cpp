#include "DBManager.h"

#include <iostream>
using namespace std;
int main()
{
	DBManager dbm(
		"Driver={ODBC Driver 17 for SQL Server};Server=.\\SQLExpress;Database=coms-tup-db;Trusted_Connection=yes;");
}
