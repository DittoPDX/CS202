/*
Steven Tran
CS202 | Program #3
Karla Fant
2/12/2017

This is the header file which contains the prototypes for the user interface.
*/

#include "Group.h"
#include "System.h"
#include <iostream>

using namespace std;

int display_menu();
int display_submenu();
int get_groups(group & g1, group & g2, system & ebs);
int menu(system & ebs, group *& list, int option);
