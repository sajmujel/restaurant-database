#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#include "../main.h"
#include "restaurant.h"
#include "ratings.h"
#include "utils.h"
#include "constants.h"

// MAIN STRUCT
typedef struct Restaurant	
{
	char name[NAME_LEN];
	char address[ADD_LEN];
	int rating;
	char comment[COM_LEN];
	struct Restaurant* next;	// linked list structure
} Restaurant;

// head is the start of linked list	// headOfLinkedList -> [res1] -> [res2] -> NULL
Restaurant* headOfLinkedList = NULL;

// GLOBAL VARIABLES
FILE* pFile;


											// HELPER FUNCTIONS
// used at beginning to allocate new linked list from file, opens file in read mode - scans values to linked list
void loadRestaurantsFromFile()
{
	pFile = fopen(DATABASE_NAME, "r");		// opening file in read mode
	if (pFile == NULL)
	{
		printf("Could not open file!");
		return;
	}		// if null return

	char line[BUFFER_SIZE];	// temporary line buffer (string)	 one line will be stored here

	while (fgets(line, sizeof(line), pFile))		// loop throught one line at the time from file to "line"
		// fgets returns NULL once theres no more lines
	{
		Restaurant* pRestaurant = (Restaurant*)malloc(sizeof(Restaurant));	// memory for Restaurant size
		if (pRestaurant == NULL)
		{
			printf("Memory allocation failed!\n");
			fclose(pFile);
			exit(0);
		}

		pRestaurant->next = NULL;

		sscanf(line, "Restaurant name: %[^|] | Address: %[^|] | Rating: %d | Comment: %[^\n]",
			pRestaurant->name, pRestaurant->address, &pRestaurant->rating, pRestaurant->comment);

		// sscanf similar to scanf but reads string instead of stdin
		// searching for pattern from line and extracts name and add from it 

		if (headOfLinkedList == NULL)
			headOfLinkedList = pRestaurant;		// adding node to the linked list
		else
		{
			Restaurant* temp = headOfLinkedList;
			while (temp->next)
			{
				temp = temp->next;
			}
			temp->next = pRestaurant;
		}
	}
	fclose(pFile);
}
// used in add delete edit etc. if database == empty, calls returnFunction on any key, used for going back to menu
void returnToMenu(const char* sectionText, void (*returnFunction)())
{
	printf("No restaurant to %s.\n", sectionText);
	waitForSec(1);
	printf("\n");
	printf("Press any key to exit.\n");
	getch();
	returnFunction();
}
// used at either exiting program or when head == NULL, frees memory from malloc
void freeRestaurants()
{
	Restaurant* temp;

	while (headOfLinkedList != NULL)	// run while linked list is not empty
	{
		temp = headOfLinkedList;		// save current head node ( restaurant ) to "temp"
		headOfLinkedList = headOfLinkedList->next;	// move head of list pointer by one 
		free(temp);	// free temp

		//	[res1] -> [res2] -> [NULL]
		// free			free		
	}
}
// just in case malloc fails, exit program
void memoryAllocationPrevention(void* ptr)
{
	if (ptr == NULL)
	{
		printf("Memory allocation failed!\n");
		exit(0);	// 0 for exit success
	}
}
// used for printing restaurant from linked list
void printResList(void* ptr)
{
	Restaurant* pRestaurant = (Restaurant*)ptr;
	int resIndex = 1;
	printf("			***LIST OF RESTAURANTS***\n\n");

	while (pRestaurant != NULL)
	{
		printf("%d. ", resIndex);
		printf("Restaurant name : %s | Address : %s | Rating : %d | Comment : %s\n",
			pRestaurant->name, pRestaurant->address, pRestaurant->rating, pRestaurant->comment);
		pRestaurant = pRestaurant->next; resIndex++;
	}
}
// used to give repeat choice to user (add,etc.), yes user types Y it calls yesFunction() if N calls noFunction()
void getYesNoChoice(const char* printfTextFill, void (*yesFunction)(), void(*noFunction)())
{
	char choice = '\0';

	printf("Do you want to %s another restaurant? (y/n) \n", printfTextFill);
	do
	{
		choice = getch();
		choice = tolower(choice);		// if Y or N written in uppercase - make it lowercase
	} while (choice != 'y' && choice != 'n');	// loop while n or y written

	switch (choice)
	{
	case 'y': yesFunction(); break; // reset loop on "yes"
	case 'n': loadingText(L_LOADING_STRING); noFunction(); break;
	}
}
// used for geting user input (which restaurant user chose to delete etc.)
int getRestaurantIndex(const char* printTextFill, int resCount)
{
	int returnIndex = 0;
	char buffer[BUFFER_SIZE];

	do
	{
		printf("\nSelect restaurant to %s (1 - %d): ", printTextFill, resCount);
		fgets(buffer, sizeof(buffer), stdin);
		if (sscanf(buffer, "%d", &returnIndex) != 1 || returnIndex < 1 || returnIndex > resCount)
		{
			printf("Invalid input! Please enter a number between 1 and %d.\n", resCount);
			continue;
		}
		break;
	} while (1);
	return returnIndex;
}
// used to get count of how many restaurants are currently in database, returns restaurant count
int getRestaurantCount(void* ptr)
{
	Restaurant* pRestaurant = (Restaurant*)ptr;

	int num = 0;

	while (pRestaurant != NULL) // looping through ptr
	{
		pRestaurant = pRestaurant->next;
		num++;
	}
	return num;
}
// used in add to append to database file, opens file in append mode then scans values from linked list into file
void appendFile(void* ptr)
{
	Restaurant* pRestaurant = (Restaurant*)ptr;

	pFile = fopen(DATABASE_NAME, "a");			//opening file in append mode

	if (pFile == NULL)			// null file prevention
	{
		printf("Could not open file!\n");
		free(pRestaurant);		// free memory from malloc if file could not be opened
		return;
	}

	fprintf(pFile, "Restaurant name: %s | Address: %s | Rating: %d | Comment: %s\n", //file printf, in "" is format in which it will be written into file
		pRestaurant->name, pRestaurant->address, pRestaurant->rating, pRestaurant->comment);	// writing into file
	fclose(pFile);		// close file

	printf("Restaurant added successfully!\n");
}
// used to overwrite file on any changes made, editing deleting etc.
void overwriteFile(void* ptr)
{
	Restaurant* pRestaurant = (Restaurant*)ptr;

	pFile = fopen(DATABASE_NAME, "w");
	if (pFile == NULL)
	{
		printf("Could not open file.\n");
		return;
	}

	while (pRestaurant != NULL)
	{
		fprintf(pFile, "Restaurant name: %s | Address: %s | Rating: %d | Comment: %s\n",
			pRestaurant->name, pRestaurant->address, pRestaurant->rating, pRestaurant->comment);
		pRestaurant = pRestaurant->next;
	}
	fclose(pFile);
}

												// MAIN FUNCTIONS

void addRestaurant()
{
	clearConsole();

	Restaurant* pRestaurant = (Restaurant*)malloc(sizeof(Restaurant));	// malloc with size of struct 

	memoryAllocationPrevention(pRestaurant);	// if pRes is NULL program will exit

	// filling node
	printf("Restaurant name: \n");
	fgets(pRestaurant->name, sizeof(pRestaurant->name), stdin);	// scanf with spaces, stdin = standart input
	trimNewline(pRestaurant->name);			// trim line created by fgets

	printf("Restaurant address: \n");
	fgets(pRestaurant->address, sizeof(pRestaurant->address), stdin);
	trimNewline(pRestaurant->address);

	pRestaurant->rating = 0;	// set default rating to 0

	strcpy(pRestaurant->comment, "No Comment");		// set default comment to 'No comment' to prevent garbage in output
	trimNewline(pRestaurant->comment);
	pRestaurant->next = NULL;	// we created last node in list so we need to point to NULL [head] -> [HERE] -> NULL

	if (headOfLinkedList == NULL) // if head == null  == no restaurant in linked list yet
	{
		headOfLinkedList = pRestaurant;	// assign first restuanrat [pRestaurant] -> [headOfLinkedList(NULL)]
	}
	else
	{
		Restaurant* temp = headOfLinkedList;	// temp = copy pointer of head

		while (temp->next != NULL)	// loop until temp.next is not null, so we dont go to restaurant that has 'next' pointer to NULL
		{
			temp = temp->next;	// move temp one x	y one [res1] -> [res2] -> [NULL]
			//   temp  -> move temp here ...
		}
		temp->next = pRestaurant;	// attaching pRestaurant to the end of linkedList
	}

	appendFile(pRestaurant);

	waitForSec(1);

	getYesNoChoice(ADD_STRING, addRestaurant, managementSection);
}

void editRestaurant()
{
	clearConsole();

	if (headOfLinkedList == NULL)		// if null go to management section
	{
		returnToMenu(EDIT_STRING, managementSection); return;
	}

	Restaurant* temp = headOfLinkedList;

	printResList(temp);
	int count = getRestaurantCount(temp);

	int editIndex = getRestaurantIndex(EDIT_STRING, count);

	temp = headOfLinkedList;

	for (int i = 1; i < editIndex; i++)	// find res that matches 
	{
		temp = temp->next;
	}

	char buffer[BUFFER_SIZE];
	int sectionChoice = 0;

	do
	{
		printf("\nYou selected: %d. %s\n", editIndex, temp->name);
		printf("Which section would you like to edit (1 - 3):\n");
		printf("1. Restaurant name\n");
		printf("2. Restaurant address\n");
		printf("3. Restaurant rating\n");

		fgets(buffer, sizeof(buffer), stdin);

		if (sscanf(buffer, "%d", &sectionChoice) != 1 || sectionChoice < 1 || sectionChoice > 3)
		{
			printf("Invalid input! Please enter a number between 1 and 3.\n");
			continue;
		}
		break;
	} while (1);

	int newRating = 0;

	switch (sectionChoice)
	{
	case 1:
		printf("New Restaurant name: ");
		fgets(temp->name, sizeof(temp->name), stdin);
		trimNewline(temp->name);
		break;
	case 2:
		printf("New Restaurant address: ");
		fgets(temp->address, sizeof(temp->address), stdin);
		trimNewline(temp->address);
		break;
	case 3:
		do
		{
			printf("New rating (%d-%d): ", MIN_RATE, MAX_RATE);
			fgets(buffer, sizeof(buffer), stdin);
			if (sscanf(buffer, "%d", &newRating) != 1 || newRating < MIN_RATE || newRating > MAX_RATE)
			{
				printf("Invalid input! Please enter a number between %d and %d.\n", MIN_RATE, MAX_RATE);
				continue; // repeat loop
			}
			else
			{
				break;
			}
		} while (1);
		temp->rating = newRating;
		break;
	}
	temp = headOfLinkedList;

	overwriteFile(temp);

	loadingText(L_EDITING_STRING);
	printf("\nRestaurant edited successfully!\n");
	waitForSec(1);

	getYesNoChoice(EDIT_STRING, editRestaurant, managementSection);
}

void deleteRestaurant()
{
	clearConsole();

	Restaurant* temp = headOfLinkedList;

	if (headOfLinkedList == NULL)
	{
		returnToMenu(DELETE_STRING, managementSection);
		return;
	}

	printResList(temp);
	int count = getRestaurantCount(temp);

	int deleteIndex = getRestaurantIndex(DELETE_STRING, count);

	// TRAVERSAL LOGIC
	Restaurant* current;
	Restaurant* previous;		// temporary helper pointers

	current = headOfLinkedList; // set current to start of the linked list
	previous = NULL;			// previous to null - will be something later

	for (int i = 1; i < deleteIndex; i++)	// loop from 1 - index of restaurant user wish to delete
	{
		previous = current;
		current = current->next;	// move in linked list	[res1] => [res2] = NULL
	}								//						previous  current
	if (previous == NULL)
	{
		headOfLinkedList = current->next;	// if null dont move
	}
	else
	{
		previous->next = current->next;		// move nod
	}

	printf("\nDeleting restaurant: %d. %s\n", deleteIndex, current->name);
	free(current);

	temp = headOfLinkedList;	// reset temp just in case
	overwriteFile(temp);		// need to close file
	loadingText(L_DELETING_STRING);	// design

	printf("\nRestaurant deleted successfully!\n");

	waitForSec(1);

	getYesNoChoice(DELETE_STRING, deleteRestaurant, managementSection);
}

void viewRestaurant()
{
	clearConsole();

	Restaurant* temp;
	temp = headOfLinkedList;

	printResList(temp);
	int count = getRestaurantCount(temp);

	if (count == 0)
	{
		returnToMenu(VIEW_STRING, managementSection); return;
	}
	fclose(pFile);
	getch();
	managementSection();
}


/*
void searchByRating()
{
	clearConsole();

	if (headOfLinkedList == NULL)		// if null go to management section
	{
		returnToMenu(SEARCH_STRING, searchSection); return;
	}

	Restaurant* temp = headOfLinkedList;

	int choice = 0;
	char buffer[BUFFER_SIZE];

	do
	{
		printf("\Enter rating(%d - %d): ", MIN_RATE, MAX_RATE);
		fgets(buffer, sizeof(buffer), stdin);
		if (sscanf(buffer, "%d", &choice) != 1 || choice < MIN_RATE || choice > MAX_RATE)
		{
			printf("Invalid input! Please enter a number between %d and %d.\n", MIN_RATE, MAX_RATE);
			continue;
		}
		break;
	} while (1);

	bool printList = 1;
	bool foundRes = 0;

	while (temp != NULL)
	{
		if (temp->rating == choice)
		{
			if (printList)
			{
				printf("\n		LIST OF RESTAURANT WITH RATING OF %d\n", choice);
				printList = 0;
			}

			printf("Restaurant name : %s | Address : %s | Rating : %d | Comment : %s\n",
				temp->name, temp->address, temp->rating, temp->comment);
			foundRes = 1;
		}
		temp = temp->next;
	}

	if (!foundRes)
	{
		printf("No restaurant with rating of %d in databaze.\n", choice);
		waitForSec(1);
		printf("\nPress any key to return to menu.\n");
		getch();
		searchSection();
		return;
	}

		waitForSec(2);
		printf("\nPress any key to return to menu.\n");
		getch();
		searchSection();
}
void searchAplhabetically()
{
	clearConsole();

	if (headOfLinkedList == NULL)		// if null go to management section
	{
		returnToMenu(SEARCH_STRING, searchSection); return;
	}

	Restaurant* temp = headOfLinkedList;

	char choice = '\0';

		printf("\Enter first letter of restaurant name: \n");
		scanf_s("%c", &choice);

	while (temp != NULL)
	{
		if (temp->name[0] == choice)
		{
			break;
		}
		else
		{
			printf("No restaurant with rating of %c in databaze.\n", choice);
			waitForSec(1);
			printf("\nPress any key to return to menu.\n");
			getch();
			searchSection();
			return;
		}
		temp->next;
	}
	printf("\n		LIST OF RESTAURANT WITH RATING OF %c\n", choice);
	printf("Restaurant name : %s | Address : %s | Rating : %d | Comment : %s\n",
		temp->name, temp->address, temp->rating, temp->comment);

	waitForSec(2);
	printf("\nPress any key to return to menu.\n");
	getch();
	searchSection();
}
*/

void rateRestaurant()
{
	Restaurant* temp = headOfLinkedList;

	if (temp == NULL)
	{
		clearConsole();
		returnToMenu(RATE_STRING, ratingSection);
	}
	clearConsole();

	printResList(temp);

	int count = getRestaurantCount(temp);
	int rateIndex = getRestaurantIndex(RATE_STRING, count);

	for (int i = 1; i < rateIndex; i++)	// find res that matches 
	{
		temp = temp->next;
	}

	int newRating = 0;
	char buffer[BUFFER_SIZE];

	do
	{
		printf("\Rate Restaurant (%d - %d): ", MIN_RATE, MAX_RATE);
		fgets(buffer, sizeof(buffer), stdin);
		if (sscanf(buffer, "%d", &newRating) != 1 || !(newRating >= MIN_RATE) || !(newRating <= MAX_RATE))	//// do while not 1 - count
		{
			printf("Invalid input! Please enter a number between %d and %d.\n", MIN_RATE, MAX_RATE);
			continue;
		}
		break;
	} while (1);

	temp->rating = newRating;		// rewrite rating

	printf("Enter your comment: \n");
	fgets(temp->comment, sizeof(temp->comment), stdin);	// scanf with spaces, stdin = standart input
	trimNewline(temp->comment);

	overwriteFile(temp);

	loadingText(L_LOADING_STRING);
	printf("\nRestaurant rated successfully!\n");
	waitForSec(1);

	getYesNoChoice(RATE_STRING, rateRestaurant, ratingSection);
}

void searchByName()
{
	// print enter name of restaurant
	// chceck if name matches anything if not return
	// if matches display restaurant
}

void sortByRating()
{

}

void sortAplhabecitally()
{

}
