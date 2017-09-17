/*
Steven Tran
CS202 | Program #2
Karla Fant
2/02/2017

This is the header file for the user interface. The user interface will function
sort of like a game which makes accessing each individual function easier.
*/

#include <iostream>
#include <cctype>
#include <cstring>
#include "Transit.h"
#include "History.h"

using namespace std;
using namespace ride_collection;

int menu(transit **& array, int option);
int display_menu();
void retrieve(transit **& array, int option);
void cost(transit **& array, int option);
