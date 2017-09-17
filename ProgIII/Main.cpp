/*
Steven Tran
CS202 | Program #3
Karla Fant
2/12/2017

This is the main file which contains the user interface. Have fun grading this monster.
*/

#include <iostream>
#include "UserInterface.h"

using namespace std;

const int LENGTH = 100;

int main()
{
	group list[100];
	group * list_ptr = list;
	system ebs;
	char response;

	do
	{
		int option = display_menu();
		int app = menu(ebs, list_ptr, option);
	
		if (app == 0)
		{
			cout << "Keeping Portland weird!" << endl;
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
		catch(...)
		{
			cout << "Not a response :(" << endl;
		}

		cout << endl;

	} while (response == 'y');

	return 1;
}
