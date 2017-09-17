/*
Steven Tran
CS202 | Program #2
Karla Fant
2/02/2017

This is the implementation file for the user interface. This interface keeps all of the rider history and popularity interactions
together which is easy for the user to access.
*/

#include "UserInterface.h"

int menu(transit ** &array, int option)
{
	switch (option)
	{
		case 0:
		{
			return 0;
		}
		case 1:
		{
			cout << "~Bus 9-Powell~" << endl;
			array[0] -> display();
			break;
		}
		case 2:
		{
			cout << "~MAX Green Line~" << endl;
			array[1] -> display();
			break;
		}
		case 3:
		{
			cout << "~Streetcar A-Loop" << endl;
			array[2] -> display();
			break;
		}
		case 4:
		{
			
			cout << endl << "~Transportation Types~" << endl
			     << "0) Bus: 9-Powell      " << endl 
			     << "1) MAX Green Line     " << endl
			     << "2) Streetcar: A-Loop  " << endl
			     << "Enter an option: ";

			int response;
			cin >> response; cin.ignore();

			if (response < 0 || response > 2)
			{
				cout << "Oops, not an option!" << endl;
				break;
			}	
				
			retrieve(array, response);
	
			break;
		}
		case 5:
		{
			cout << endl;
			cout << "~Transportation Types~" << endl
			     << "0) Bus: 9-Powell      " << endl
			     << "1) MAX Green Line     " << endl
			     << "2) Streetcar: A-Loop  " << endl;

			cout << "Enter an option: ";
			int response;
			cin >> response; cin.ignore();
		
			if (response < 0 || response > 2)
			{
				cout << "Oops, not an option!" << endl;
				break;	
			}	

			cout << endl;	
			cost(array, response);

			break;
		}
		case 6:
		{
			char response;
			int choice;

			do
			{
				cout << endl;
				char desc[MAX], desc2[MAX];
				cout << "~Trip Experience~" << endl;
			
				cout << "0) Bus: 9-Powell" << endl
				     << "1) MAX Green Line" << endl
				     << "2) Streetcar: A-Loop" << endl
				     << "What transit type did you take? ";
				
				cin >> choice; cin.ignore();
				
				if (choice < 0 || choice > 2)
				{
					cout << "Oops, not an option!" << endl;
					break;
				}
			
				cout << "How was the trip? ";
				cin.get(desc, MAX); cin.ignore(MAX, '\n');
				strcat(desc, "\n");

				cout << "Would you ride again? ";
				cin.get(desc2, MAX); cin.ignore(MAX, '\n');
				strcat(desc2, "\n");

				strcat(desc, desc2);

				array[choice] -> add(desc);
				cout << "Experience added to the list for that transit type!" << endl << endl;	
				
				cout << "Add another (y/n)? ";
				cin.get(response); cin.ignore();

			} while (response == 'y');

			break;
		}
		case 7:
		{
			cout << "~Removing Trip Experience List~" << endl
			     << "Rule: Only removes your most recent list of top 5 experiences" << endl	
			     << "0) Bus | 1) MAX | 2) Streetcar" << endl
			     << "Choose a transit system to delete your experiences: ";

			int user_response;
			cin >> user_response; cin.ignore();
			if (user_response < 0 || user_response > 2)
			{
				cout << "Oops not an option!" << endl;
				break;
			}

			int success = array[user_response] -> remove();
			(success >= 1 ? cout << "Top 5 experiences removed!" << endl : cout << "Nothing removed" << endl);
			break;
		}
		case 8:
		{
			char response;
			cout << "Are you sure (y/n)? ";
			cin.get(response); cin.ignore();

			if (response == 'y')
			{
				int verify = 0;

				for (int i = 0; i < 3; ++i)
				{
					int success = array[i] -> remove_all();

					if (success != 0)
					{
						++verify;	
					}
				}

				(verify >= 1 ? cout << "All experiences removed!" << endl : cout << "Nothing removed!" << endl);
			}

			break;
		}
		case 9:
		{
			cout << endl;
			cout << "0) Bus" << endl
			     << "1) MAX" << endl
			     << "2) Streetcar" << endl;
			cout << "Which transit type are you looking for to display your experiences? ";
			int user_choice;
			cin >> user_choice; cin.ignore();

			if (user_choice < 0 || user_choice > 2)
			{
				cout << "Oops not an option!" << endl;
				break;	
			}
				
			cout << "~Your Experiences!~" << endl;
			array[user_choice] -> rider::display();
			break;
		}
		case 10:
		{
			cout << endl;
			cout << "0) Bus" << endl
			     << "1) MAX" << endl
			     << "2) Streetcar" << endl
			     << "Which transit type are you looking for to display your top 5 recent experiences? ";
			int user_option;
			cin >> user_option; cin.ignore();
			
			if (user_option < 0 || user_option > 2)
			{
				cout << "Oops not an option!" << endl;
				break;
			}

			cout << "~Most Recent Experience~" << endl;
			array[user_option] -> display_recent();
			
			break;
		}
		case 11:
		{
			cout << endl;
			char to_find[MAX];
			char * finder = to_find;
			cout << "~Trip Retrieval~" << endl;
			cout << "e.g. Too much weed! (enter Too for instance)" << endl;
			cout << "Locate a trip by entering the first few words: ";
			
			cin.get(finder, MAX); cin.ignore(MAX, '\n');

			cout << "0) Bus | 1) Max | 2) Streetcar" << endl;		
			cout << "Which transit type did you use? ";
			int user_option;
			cin >> user_option; cin.ignore();

			if (user_option < 0 || user_option > 2)
			{
				cout << "Oops not an option!" << endl;
				break;
			}

			int success = array[user_option] -> retrieve(finder);

			if (success == 1)
			{
				cout << finder;	
				delete [] finder;
				finder = NULL;
			}	

			break;	
		}
		case 12:
		{
			cout << endl;
			cout << "~Transit Stop Deletion~" << endl
			     << "0) Bus			" << endl
			     << "1) MAX			" << endl
		             << "2) Streetcar		" << endl
			     << "Enter an option: ";

			int option;
			cin >> option; cin.ignore();

			if (option < 0 || option > 2)
			{
				cout << "Oops, not an option" << endl;		
				break;
			}

			char stop_time[MAX];
			cout << "Enter a time slot (e.g. 12:00AM): ";
			cin.get(stop_time, MAX); cin.ignore(MAX, '\n');

			int success = array[option] -> remove_popularity(stop_time);		
			
			(success == 1 ? cout << "Time slot removed" << endl : cout << "None removed" << endl);

			break;
		}
		case 13:
		{
			cout << endl
			     << "~Transit Total Deletion~" << endl
			     << "0) Bus			 " << endl
			     << "1) MAX			 " << endl
			     << "2) Streetcar 		 " << endl
			     << "Enter an option: ";

			int opt;
			cin >> opt; cin.ignore();	

			if (opt < 0 || opt > 2)
			{
				cout << "Oops, not an option" << endl;
				break;
			}
			
			int num_removed = array[opt] -> remove_all_popularity();
		
			cout << "Time slots removed: " << num_removed << endl;

			break;	
		}
		default:
		{
			break;
		}
	}

	return 1;
}

int display_menu()
{
	cout << "~Portland Transportation Application~		" << endl
	     << "0. Exit the application	      		" << endl
	     << "1. Bus Popularity List & Service		" << endl
	     << "2. MAX Popularity List & Service" << endl
	     << "3. Streetcar Popularity List & Service	        " << endl
             << "4. Retrieve a popularity time slot   " << endl
    	     << "5. Find the cost of a transit type   " << endl
	     << "6. Enter a trip experience	      " << endl
	     << "7. Remove a list of trip experiences " << endl
	     << "8. Remove all trip experiences	      " << endl
	     << "9. Display trip experiences	      " << endl
	     << "10. Display most recent experience   " << endl
	     << "11. Find a trip experience	      " << endl
	     << "12. Delete a popularity stop         " << endl
	     << "13. Delete all stops for a transit   " << endl;

	int option;
	cout << "Select an option: ";
	cin >> option; cin.ignore();
	
	return option;

}

void retrieve(transit **& array, int option)
{
	char text[MAX];
	char * input = text;
	bool service_check = false;

	cout << "e.g. 12:00AM or 06:00AM" << endl
	     << "Enter a time slot: ";
	
	cin.get(input, MAX); cin.ignore(MAX, '\n');
	int success = array[option] -> retrieve_popularity(input, service_check);
	
	if (success == 1)
	{
		cout << input;

		if (service_check == 1)
		{
			cout << " : In-Service" << endl;
		}
		else
		{
			cout << " : Not-In-Service" << endl;
		}
	}	
	else
	{
		cout << "No time slot found" << endl;
		return;
	}

	delete [] input;
	input = NULL;
}

void cost(transit **& array, int option)
{
	array[option] -> cost();
}
