#include <Windows.h>
#include <stdio.h>
#include <windows.h>

#include "restaurant.h"

extern FILE* pFile;

void clearConsole()
{
    system("cls");
}

void clearFile()
{
	pFile = fopen("database.txt", "w");
	if (pFile == NULL)
	{
		printf("Could not open file");
        return;
	}
	fprintf(pFile,"");
}

void waitForSec(float seconds)
{
    Sleep(300/*1000*/ * seconds);
}

void trimNewline(char* str)
{
    str[strcspn(str, "\n")] = '\0';  // finds \n in str and replaces it with null terminator 

    int end = strlen(str) - 1;
    while (end >= 0 && (str[end] == ' ' || str[end] == '\t' || str[end] == '\r')) // trims trailing spaces
        str[end--] = '\0';


    int start = 0;
    while (str[start] == ' ' || str[start] == '\t' || str[start] == '\r') // trims leading spaces
        start++;

    if (start > 0)
        memmove(str, str + start, strlen(str + start) + 1);
}

void loadingText(const char* text)
{
	printf("\n\r%s.", text); fflush(stdout); waitForSec(1); // fflush forces the buffer to print immediately
	printf("\r%s..", text); fflush(stdout); waitForSec(1);
	printf("\r%s...", text); fflush(stdout); waitForSec(1); clearConsole();
}


