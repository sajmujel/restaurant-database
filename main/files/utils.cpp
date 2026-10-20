#include <Windows.h>
#include <stdio.h>
#include <windows.h>

#include "restaurant.h"

// EXTERN FILES
extern FILE* pFile;

/*void clearConsole()
{
#ifdef _WIN32
	system("cls");   // Windows
#else
	system("clear"); // Linux / macOS
#endif

	//printf("\033[H\033[J");
}*/
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>
#endif

void clearConsole()
{
#ifdef _WIN32
    // Windows method 1: system("cls")
    system("cls");

    // Optional: make sure the cursor is at the top-left
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole != INVALID_HANDLE_VALUE)
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if (GetConsoleScreenBufferInfo(hConsole, &csbi))
        {
            COORD topLeft = { 0, 0 };
            DWORD written;
            FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X * csbi.dwSize.Y, topLeft, &written);
            FillConsoleOutputAttribute(hConsole, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, topLeft, &written);
            SetConsoleCursorPosition(hConsole, topLeft);
        }
    }
#else
    // Linux / macOS
    printf("\033[H\033[J"); // ANSI escape: move cursor to top-left and clear screen
#endif
}


void clearFile()
{
	pFile = fopen("database.txt", "w");
	if (pFile == NULL)
	{
		printf("Could not open file");
	}
	fprintf(pFile,"");
}

void waitForSec(float seconds)
{
	Sleep(800/*1000*/ * seconds);
}

void trimNewline(char* str)
{
	str[strcspn(str, "\n")] = '\0';  // find '\n' and replace with '\0'
}

void loadingText(const char* text)
{
	printf("\n\r%s.", text); fflush(stdout); waitForSec(1);
	printf("\r%s..", text); fflush(stdout); waitForSec(1);
	printf("\r%s...", text); fflush(stdout); waitForSec(1); clearConsole();
}


