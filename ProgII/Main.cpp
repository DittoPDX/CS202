/*
Steven Tran
CS202 | Program #2
Karla Fant
2/02/2017

This is the main file which preloads the transit data needed. Most of the interface comes from UserInterface.h
which implements all of the necessary functions for user interaction.
*/

#include <iostream>
#include "Transit.h"
#include "UserInterface.h"

using namespace std;
using namespace ride_collection;

int main()
{
	/*Preload the data*/
	//Transit is an abstract base class pointer to three different derived classes.
	transit * array[3];
	char file[MAX] = "Streetcar.txt";
	char file2[MAX] = "MAX.txt";
	char file3[MAX] = "Bus.txt";
	array[0] = new bus;
	array[0] -> load(file3);
	array[1] = new max_train;
	array[1] -> load(file2);
	array[2] = new streetcar;
	array[2] -> load(file);
	/*****************/

	//Load the data for the menu interface.
	//rider transit_user;
	transit ** ptr = array;	
	char response;

	do
	{
		int option = display_menu();
		int app = menu(ptr, option);
		
		if (app == 0)
		{
			cout << "Keeping Portland weird!" << endl;

			for (int i = 0; i < 3; ++i)
			{
				if (ptr[i])
				{
					delete ptr[i];
					ptr[i] = NULL;
				}
			}

			return 0;
		}

		try
		{
			cout << "Again (y/n)? ";
			cin.get(response); cin.ignore();

			if (response != 'y' && response != 'n')
			{
				throw response;				
			}
		}
		catch (...)
		{
			cout << "Not a response :(" << endl;
		}
		
		cout << endl;

	} while ('y' == response);

	//Deallocate all of the data within transit array.
	for (int i = 0; i < 3; ++i)
	{
		if (ptr[i])
		{
			delete ptr[i];
			ptr[i] = NULL;
		}
	}

	return 0;
}
