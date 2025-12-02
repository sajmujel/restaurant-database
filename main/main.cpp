#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#include "main.h"
#include "files/restaurant.h"
#include "files/utils.h"
#include "files/constants.h"

void displayMenu();

void searchSection();
void managementSection();
void ratingSection();

void displayManagementSection();
void displayRatingSection();
void displaySearchSection();

bool isRunning = true;

int main()
{
	loadRestaurantsFromFile();	// load restaurants from file into memory
	//clearFile();

	int choice = 0;	

	while (isRunning)
	{
			clearConsole();
			displayMenu();
			choice = getch();

			switch (choice)
			{
			case '0': loadingText(L_EXITING_STRING); freeRestaurants(); exit(0); break;
			case '1': managementSection(); break;
			case '2': ratingSection(); break;
			case '3': searchSection();	break;
			default: printf("\nInvalid input.\n"); waitForSec(1); break;
			}
	}
		return 0;
}
							//  MAIN MENU
void displayMenu()
{
	puts("======================");
	puts("|   RESTAURANT APP   |");
	puts("|====================|");
	puts("|                    |");
	puts("|   [1] Management   |");
	puts("|   [2] Rating       |");
	puts("|   [3] Search       |");
	puts("|   [0] Exit         |");
	puts("|____________________|");
}
							// MANAGEMENT SECTION
void managementSection()
{
		isRunning = false;
		clearConsole();
		displayManagementSection();

		int choice = 0;
		choice = getch();
		switch (choice)
		{
		case '0': isRunning = true; break;
		case '1': addRestaurant(); break;
		case '2': editRestaurant(); break;
		case '3': deleteRestaurant(); break;
		default: printf("\nInvalid input.\n"); waitForSec(1); managementSection(); break;
		}
}

void displayManagementSection()
{
	puts("======================");
	puts("|     MANAGEMENT     |");
	puts("|====================|");
	puts("|                    |");
	puts("|   [1] Add          |");
	puts("|   [2] Edit         |");
	puts("|   [3] Delete       |");
	puts("|   [0] Go Back      |");
	puts("|____________________|");
}
							// RATING SECTION
void ratingSection()
{
	isRunning = false;
	clearConsole();
	displayRatingSection();
	int choice = 0;
	choice = getch();
	switch (choice)
	{
	case '0': isRunning = true; break;
	case '1': rateRestaurant(); break;
	case '2': viewRestaurant(); break;
	default: printf("\nInvalid input.\n"); waitForSec(1); ratingSection(); break;
	}
}

void displayRatingSection()
{
	puts("======================");
	puts("|       RATING       |");
	puts("|====================|");
	puts("|                    |");
	puts("|   [1] Rate         |");
	puts("|   [2] See ratings  |");
	puts("|   [0] Go Back      |");
	puts("|____________________|");
}
							// SEARCH SECTION
void searchSection()
{
	isRunning = false;
	clearConsole();
	displaySearchSection();

	int choice = 0;
	choice = getch();
	switch (choice)
	{
	case '0': isRunning = true; break;
	case '1': searchByRating(); break;
	case '2': sortByRating(); break;
	case '3': searchAlphabetically(); break;
	case '4': sortAlphabetically(); break;
	default: printf("\nInvalid input.\n"); waitForSec(1); searchSection(); break;
	}
}

void displaySearchSection()
{
	puts("======================");
	puts("|     SEARCHING      |");
	puts("|====================|");
	puts("|                    |");
	puts("|     BY RATING      |");
	puts("|   [1] Search       |");
	puts("|   [2] Sort         |");
	puts("|                    |");
	puts("|   ALPHABETICALLY   |");
	puts("|   [3] Search       |");
	puts("|   [4] Sort         |");
	puts("|                    |");
	puts("|   [0] Go Back      |");
	puts("|____________________|");
}
