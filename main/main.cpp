#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#include "main.h"
#include "files/restaurant.h"
#include "files/utils.h"
#include "files/ratings.h"
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
	puts(" _____________________________________________");
	puts("|                                             |");
	puts("|       ******************************        |");
	puts("|          🍽️  RESTAURANT DATABASE  🍽️      |");
	puts("|               =-< MAIN MENU >-=             |");
	puts("|                                             |");
	puts("|                1. Management                |");
	puts("|                2. Rating                    |");
	puts("|                3. Search                    |");
	puts("|                0. Exit                      |");
	puts("|                                             |");
	puts("|            ********************             |");
	puts("|_____________________________________________|");
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
		case'4': viewRestaurant();break;
		default: printf("\nInvalid input.\n"); waitForSec(1); managementSection(); break;
		}
}

void displayManagementSection()
{
	puts(" _____________________________________________");
	puts("|                                             |");
	puts("|       ******************************        |");
	puts("|        🍴  RESTAURANT MANAGEMENT 🍴         |");
	puts("|               =-< MENU >-=                  |");
	puts("|                       4.view                 |");
	puts("|              1. Add Restaurant              |");
	puts("|              2. Edit Restaurant             |");
	puts("|              3. Delete Restaurant           |");
	puts("|              0. Go Back                     |");
	puts("|                                             |");
	puts("|            ********************             |");
	puts("|_____________________________________________|");
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
	case '2': seeRatings(); break;
	default: printf("\nInvalid input.\n"); waitForSec(1); ratingSection(); break;
	}
}

void displayRatingSection()
{
	puts(" _____________________________________________");
	puts("|                                             |");
	puts("|       ******************************        |");
	puts("|          🌟  RATING SECTION  🌟             |");
	puts("|               =-< MENU >-=                  |");
	puts("|                                             |");
	puts("|              1. Rate a Restaurant           |");
	puts("|              2. See Ratings                 |");
	puts("|              0. Go Back                     |");
	puts("|                                             |");
	puts("|            ********************             |");
	puts("|_____________________________________________|");
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
	case '1': printf("search\n"); break;
	case '2': printf("search\n"); break;
	default: printf("\nInvalid input.\n"); waitForSec(1); searchSection(); break;
	}
}

void displaySearchSection()
{
		puts(" _____________________________________________");
		puts("|                                             |");
		puts("|       ******************************        |");
		puts("|           🔍  SEARCH SECTION  🔍            |");
		puts("|               =-< MENU >-=                  |");
		puts("|                                             |");
		puts("|              1. Search by Rating            |");
		puts("|              2. Search Alphabetically       |");
		puts("|              0. Go Back                     |");
		puts("|                                             |");
		puts("|            ********************             |");
		puts("|_____________________________________________|");
}
