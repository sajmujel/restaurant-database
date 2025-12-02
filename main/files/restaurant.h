#pragma once
#include "constants.h"

void addRestaurant(); 
void editRestaurant(); 
void deleteRestaurant();
void loadRestaurantsFromFile();
void freeRestaurants();
void viewRestaurant();
void searchByRating();
void rateRestaurant();
void returnToMenu(const char* sectionText, void (*returnFunction)());
void memoryAllocationPrevention(void* ptr);
void appendFile(void* ptr);
void getYesNoChoice(const char* printfTextFill, void (*yesFunction)(), void(*noFunction)());
int getRestaurantCount(void* ptr);
void printResList(void* ptr);
int getRestaurantIndex(const char* printTextFill, int resCount);
void overwriteFile(void* ptr);
void addMenuItem(void* ptr, char foodName[FOOD_LEN], float foodPrice);
void sortRestaurantsAlphabetically(void* ptr, bool a_z);
void sortRestaurantByRating(void* ptr, bool choice);

//void viewMenu();
//void addMenu();
void sortByRating();
void searchAlphabetically();
void sortAlphabetically();


