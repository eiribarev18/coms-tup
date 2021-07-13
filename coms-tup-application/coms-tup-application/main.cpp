#include "DBManager.h"
#include "console_io.h"
#include "env.h"

using namespace std;

int main()
{
	DBManager dbm(CT_DRIVER, CT_SERVER, CT_DATABASE);

	while (loginMenu(dbm)) {};
}
