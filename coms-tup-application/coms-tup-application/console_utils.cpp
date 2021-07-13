#include "console_io.h"

#include <Windows.h>
#include <iostream>

using namespace std;

void clearConsole()
{
	// Thank you, Microsoft <3
	// https://docs.microsoft.com/en-us/windows/console/clearing-the-screen

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SMALL_RECT scrollRect;
	COORD scrollTarget;
	CHAR_INFO fill;
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	if (hConsole == INVALID_HANDLE_VALUE) { return; }

	// Get the number of character cells in the current buffer.
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) { return; }

	// Scroll the rectangle of the entire buffer.
	scrollRect.Left = 0;
	scrollRect.Top = 0;
	scrollRect.Right = csbi.dwSize.X;
	scrollRect.Bottom = csbi.dwSize.Y;

	// Scroll it upwards off the top of the buffer with a magnitude of the entire height.
	scrollTarget.X = 0;
	scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

	// Fill with empty spaces with the buffer's default text attribute.
	fill.Char.UnicodeChar = TEXT(' ');
	fill.Attributes = csbi.wAttributes;

	// Do the scroll
	ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

	// Move the cursor to the top left corner too.
	csbi.dwCursorPosition.X = 0;
	csbi.dwCursorPosition.Y = 0;

	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

void toggleEcho()
{
	HANDLE hConsole;
	DWORD mode;

	hConsole = GetStdHandle(STD_INPUT_HANDLE);

	if (hConsole == INVALID_HANDLE_VALUE) return;

	if (GetConsoleMode(hConsole, &mode)) {
		mode ^= ENABLE_ECHO_INPUT;
		SetConsoleMode(hConsole, mode);
	}
}

void printNewlines(unsigned count)
{
	for (unsigned i = 0; i < count; i++) {
		cout << endl;
	}
}
