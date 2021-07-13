#pragma once

#include "DBManager.h"

bool loginMenu(DBManager &db);

void clearConsole();
void toggleEcho();
void printNewlines(unsigned count = 1);
