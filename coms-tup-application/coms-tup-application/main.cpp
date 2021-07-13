#include "DBManager.h"
#include "env.h"
#include "console_io.h"

using namespace std;

int main()
{
	DBManager dbm(CT_DRIVER, CT_SERVER, CT_DATABASE);

	while(loginMenu(dbm));
}
