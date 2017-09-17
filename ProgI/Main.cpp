/*
Steven Tran
CS202 | Program #1 | OOP Streetcar Scheduling Program
Karla Fant
01/27/2016

This is the main file which represents the client program.
I have included a menu and menu display for organization.

For grader information:
1. Create streetcar first.
2. Then you can simply run each streetcar.
3. Pacing is set to 4 by DEFAULT.
	-You can change the pacing from one of the menu options.
*/

#include <iostream>
#include "Map.h"
#include "Type.h"

using namespace std;

int menu(graph & streetcar_map, loop & aloop, nsline & line, int option);
int displayMenu();

int menu(graph & streetcar_map, loop & aloop, nsline & line, int option)
{
	switch (option)
	{
		case 0:
		{
			return 0;
		}
		case 1:
		{
			cout << "~Portland Streetcar List of Stops~" << endl;
			int success = streetcar_map.display_all();

			if (!success)
			{
				cout << "No stops to display" << endl;			
			}

			cout << endl;
			break;
		}
		case 2:
		{
			cout << "~A-Loop Stops~" << endl;
			int success = streetcar_map.display_loop();

			if (!success)
			{
				cout << "No stops to display" << endl;
			}

			cout << endl;
			break;
		}
		case 3:
		{
			cout << "~NS-Line Stops~" << endl;
			streetcar_map.display_line();
			cout << endl;
			break;
		}
		case 4:
		{	
			char stop[MAX];
			cout << "Enter a stop to find its next stop: ";
			cin.get(stop, MAX); cin.ignore(MAX, '\n');
			int success = streetcar_map.display_adjacent(stop);	

			success == 1 ? cout << "Street connection found!" << endl : cout << "No other street connections available." << endl << endl;
			break;
		}
		case 5:
		{
			char name[MAX], location[MAX], pace[MAX] = "4";
			char status_option, response;
			int line_option = 0;
			bool service;

			do
			{
				cout << "Enter the streetcar name: ";
				cin.get(name, MAX); cin.ignore(MAX, '\n');
				cout << "In service (y/n): ";
				cin.get(status_option);	cin.ignore();
			
				status_option == 'y' ? service = true : service = false;

				cout << "(1) A-Loop | (2) NS-Line" << endl;
				cout << "Choose a line (1, 2): ";
				cin >> line_option; cin.ignore();

				if (line_option == 1)
				{
					cout << "(A-Loop) Streetcar starting location: ";
					cin.get(location, MAX); cin.ignore(MAX, '\n');
		
					int verify = aloop.verify_car_location(location);
					while (verify != 1)
					{
						cout << "~List of Stops Available" << endl;
						aloop.display_stops();
						cout << "Streetcar starting location: ";
						cin.get(location, MAX); cin.ignore(MAX, '\n');
						verify = aloop.verify_car_location(location);
					}

					streetcar to_add(name, location, service, pace);
					aloop.add_streetcar(to_add);
				}
				else if (line_option == 2)
				{
					cout << "(NS-Line) Streetcar starting location: ";
					cin.get(location, MAX); cin.ignore(MAX, '\n');

					int verify = line.verify_car_location(location);
					while (verify != 1)
					{
						cout << "~List of Stops Available" << endl;
						line.display_stops();
						cout << "Streetcar starting location: ";
						cin.get(location, MAX); cin.ignore(MAX, '\n');
						verify = line.verify_car_location(location);
					}
			
					streetcar to_add(name, location, service, pace);
					line.add_streetcar(to_add);	
				}

				cout << "Add another streetcar (y/n)? ";
				cin.get(response); cin.ignore();

			} while('y' == response || 'Y' == response);

			break;
		}
		case 6:
		{
			char input[MAX];
			cout << "Enter a streetcar to trace: ";
			cin.get(input, MAX); cin.ignore(MAX, '\n');

			int check_one = aloop.trace(input);
			int check_two = line.trace(input);

			if ((check_one + check_two) <= 0)
			{
				cout << "No streetcar found to be traced." << endl;
			}
		
			break;
		}
		case 7:
		{
			cout << "Streetcars on A-Loop" << endl;
			aloop.display_all_cars();
			cout << endl;

			cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

			cout << "Streetcars on NS-Line" << endl;
			line.display_all_cars();	
			cout << endl;

			break;
		}
		case 8:
		{
			int line_option = 0;
			char streetcar[MAX];			

			cout << "(1) A-Loop | (2) NS-Line" << endl;
			cout << "Which line are you using (1, 2)? ";

			cin >> line_option; cin.ignore();

			if (line_option == 1)
			{
				cout << "~Accessing A-Loop~" << endl;
				cout << "Which streetcar are you using? ";
				cin.get(streetcar, MAX); cin.ignore(MAX, '\n');

				int verify = aloop.verify_car_name(streetcar);
				if (verify == -2)
				{
					cout << "No cars on the line." << endl;
					return 0;
				}

				while (verify != 1)
				{
					aloop.display_all_cars();
					cout << "Which streetcar are you using? ";
					cin.get(streetcar, MAX); cin.ignore(MAX, '\n');
					verify = aloop.verify_car_name(streetcar);	
				}	
		
				bool before_run = aloop.check_service(streetcar);
				if (before_run == true)
				{
					int run_success = aloop.run_streetcar(streetcar);
					if (run_success == 1)
					{
						cout << "Streetcar has moved one stop!" << endl;
					}
					else if (run_success == -2)
					{
						cout << "Due to the pacing, this streetcar cannot move." << endl;
					}
					else if (run_success == -3)
					{
						cout << "Due to the pacing, this streetcar cannot move." << endl;
					}
				}
				else
				{
					cout << "The streetcar is currently out of service." << endl;
				}
			}
			else if (line_option == 2)
			{
				cout << "~Accessing NS-Line~" << endl;
				cout << "Which streetcar are you using? ";
				cin.get(streetcar, MAX); cin.ignore(MAX, '\n');
				
				int verify = line.verify_car_name(streetcar);
				if (verify == -2)
				{
					cout << "No cars on the line." << endl;
					return 0;
				}

				while (verify != 1)
				{
					line.display_all_cars();
					cout << "Which streetcar are you using? ";
					cin.get(streetcar, MAX); cin.ignore(MAX, '\n');
					verify = line.verify_car_name(streetcar);
				}

				bool before_run = line.check_service(streetcar);
				if (before_run == true)
				{	
					int run_success = line.run_streetcar(streetcar);
					if (run_success == 1)
					{
						cout << "Streetcar has moved one stop!" << endl;
					}
					else if (run_success == 0)
					{
						cout << "Due to the pacing, this streetcar cannot run." << endl;
					}
					else if (run_success == -3)
					{
						cout << "Due to the pacing, this streetcar cannot run." << endl;
					}
				}
				else
				{
					cout << "The streetcar is currently out of service." << endl;
				}
			}
						
			break;		
		}
		case 9:
		{
			char car_name[MAX];
			char pace_change[MAX];

			cout << "Enter in the streetcar's name to change its pace: ";
			cin.get(car_name, MAX); cin.ignore(MAX, '\n');
		
			cout << "Enter in the pace number: ";
			cin.get(pace_change, MAX); cin.ignore(MAX ,'\n');

			int success1 = aloop.change_streetcar_pace(car_name, pace_change);
			int success2 = line.change_streetcar_pace(car_name, pace_change);	

			if (success1 == -1 && success2 == -1)
			{
				cout << "No streetcars found." << endl;
			}

			break;
		}
		case 10:
		{
			cout << "By taking a streetcar out of service, it will no longer be able to run" << endl;
			cout << "----------------------------------------------------------------------" << endl;
			cout << "Enter a streetcar you want to take out of service: ";
	
			char input[MAX];
			cin.get(input, MAX); cin.ignore(MAX, '\n');
	
			int check_one = aloop.stop_service(input);
			int check_two = line.stop_service(input);
	
			if ((check_one + check_two) == 0)
			{
				cout << "No other streetcar was not found." << endl;
			}

			break;
		}
		case 11:
		{
			cout << "If you take a streetcar back into service, it will be able to run again!" << endl;
			cout << "------------------------------------------------------------------------" << endl;
			cout << "Enter a streetcar you want to start service again: ";
			
			char input[MAX];
			cin.get(input, MAX); cin.ignore(MAX, '\n');

			int check_one = aloop.start_service(input);
			int check_two = line.start_service(input);
		
			if ((check_one + check_two) == 0)
			{
				cout << "No other streetcar was not found." << endl;
			}

			break;
		}
		default:
			break;
	}

	return 0;
}

int displayMenu()
{
	int option = -1;
	
	cout << "Interactive Portland Streetcar Map	      " << endl
	     << "**********************************	      " << endl
	     << "(0) Exit the program			      " << endl
	     << "**********************************	      " << endl
	     << "~Map Functions~			      		~Line Functions~" 		<< endl
	     << "(1) Display all available stops	      		(5) Add a streetcar to a line"    << endl
    	     << "(2) Display all of Loop A's stops	      	(6) Trace a streetcar's info"     << endl
	     << "(3) Display all of NS Line's stops	      	(7) Find all streetcar's infos"   << endl
	     << "(4) Display other stops connected to a stop  " << endl
		/*
	     << endl
	     << "~Line functions~			      " << endl
	     << "(5) Add a streetcar to a line		      " << endl
	     << "(6) Trace a streetcar's info		      " << endl
	     << "(7) Find all streetcars' infos	              " << endl
		*/
	     << endl
	     << "~Streetcar Functions~			      " << endl
             << "(8) Run a streetcar (moves one stop)         " << endl
	     << "(9) Change the PACE of a streetcar           " << endl
	     << "(10) Take a streetcar out of service         " << endl
	     << "(11) Take a streetcar back into service      " << endl
	     << endl;	

	cout << "Enter a number: ";
	cin >> option; cin.ignore();
	cout << endl;

	return option;
}

int main()
{
	char response;

	/*Preloaded data for two streetcar lines.*/
	/*Saves grader's time.*/
	/************************************************************/
	graph streetcar_map;
	streetcar_map.load("A-Loop.txt");
	streetcar_map.connect_loop_stops();
	streetcar_map.load("NS-Line.txt");
	streetcar_map.connect_loop_stops2();

	char loop_name[MAX] = "A-Loop";
	char line_name[MAX] = "NS-Line";

	loop aloop(loop_name);
	aloop.load("A-Loop.txt");
	nsline line(line_name);
	line.load("NS-Line.txt");

	/************************************************************/
	do
	{
		int option = displayMenu();
		menu(streetcar_map, aloop, line, option);

		if (option == 0)
		{
			cout << "Keeping Portland weird!" << endl;
			return 0;
		}

		cout << "Continue using the program (y/n)? ";

		cin.get(response); cin.ignore();
		cout << endl;

	} while ('y' == response || 'Y' == response);

	return 0;
}
