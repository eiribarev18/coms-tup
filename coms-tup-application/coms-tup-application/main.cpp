#include "DBManager.h"
#include "env.h"

#include <iostream>

using namespace std;

int main()
{
	DBManager dbm(CT_DRIVER, CT_SERVER, CT_DATABASE);
}
