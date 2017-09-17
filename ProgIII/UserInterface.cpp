/*
Steven Tran
CS202 | Program #3
Karla Fant
2/17/2017

This is the user interface file where all of the cases are handled as a result of
user input. The operator overloading for the relational operators (<, >, <=, >=) is
available in option number 10.
*/

#include "UserInterface.h"

int menu(system & ebs, group *& list, int option)
{
	switch (option)
	{
		case 0:
		{
			return 0;
		}
		case 1:
		{
			group temp;
			temp.read();

			int check = ebs.find(temp);

			if (check == 1)
			{
				cout << "Group already exists" << endl;
			}
			else	
			{
				cout << "Group added to EBS system!" << endl;	
				ebs.add(temp);
			}

			break;
		}
		case 2:
		{
			cout << "Which group would you like to add the person to? ";
			char user_input[100]; char response;
			cin.get(user_input, 100); cin.ignore(100, '\n');

			if (ebs == user_input)
			{
				do
				{
					person to_add;
					to_add.read(user_input);

					ebs.add_person(user_input, to_add);	
					cout << "Add another person (y/n)? ";
					cin.get(response); cin.ignore();

				} while (response == 'y');

				return 1;
			}	
			else
			{
				cout << "Group doesn't exist..." << endl;
			}

			break;
		}
		case 3:
		{
			cout << "Enter the group's last name you want to remove the person in: ";
			char input[100]; group temp;
			cin.get(input, 100); cin.ignore(100, '\n');
	
			if (ebs.find(input, temp) == true)
			{
				cout << "Enter the person's name: ";
				char input2[100];
				cin.get(input2, 100); cin.ignore(100, '\n');
			
				int remove = ebs.remove_person(input, input2);
				//cout << "Remove value: " << remove << endl;
				(remove == 1 ? cout << "Remove Success!" << endl : cout << "Remove Failure" << endl);
			}
			else
			{
				cout << "Group doesn't exist..." << endl;
			}

			break;
		}
		case 4:
		{
			cout << "Enter the group's last name you want to find the person in: ";
			char input[100];
			group temp;
			cin.get(input, 100); cin.ignore(100, '\n');
	
			int check = ebs.find(input, temp);

			if (check != 1)
			{
				cout << "No group found" << endl;
				return 1;
			}

			char input2[100];
			cout << "Enter the person's name: ";
			cin.get(input2, 100); cin.ignore(100, '\n');

			char * if_found;
			char * contacts[3];
			char ** ptr = contacts;	
			int success = ebs.find_person(input2, if_found, ptr);
	
			if (success == 1)
			{	
				for (int i = 0; i < 3; ++i)
				{
					cout << "Contact Info #" << i + 1 << ": " << ptr[i] << endl;
				}	

				for (int i = 0; i < 3; ++i)
				{
					delete [] contacts[i];
				}

				if (if_found)
				{
					delete [] if_found;
				}
			}
			else
			{
				cout << "Person not found!" << endl;
			}

			break;
		}
		case 5:
		{
			char input[100]; group temp;
			cout << "Which group are you looking for to remove everyone in? ";
			cin.get(input, 100); cin.ignore(100, '\n');

			int check = ebs.find(input, temp);

			if (check == 1)
			{
				cout << "Everyone in " << input << " is removed! " << endl;
				ebs.remove_everyone_group(input);
			}
			else
			{
				cout << "Group not found :(" << endl;
			}

			break;
		}	
		case 6:
		{
			cout << "Enter the group's last name you want to see the list of people: ";
			
			
			char input[100];
			group temp;
			cin.get(input, 100); cin.ignore(100, '\n');

			int success = ebs.find(input, temp);

			if (success == 1)
			{
				temp.display();
			}
			else
			{
				cout << "No group found in the EBS system " << endl;
			}
			break;
		}
		case 7:
		{
			cout << "Enter a group name you want to find and its info: ";
			char input[100];
			cin.get(input, 100); cin.ignore(100, '\n');
		
			group temp;
	
			int success = ebs.find(input, temp);

			if (success == 1)
			{
				temp.display();
			}	
			else
			{
				cout << "Not found!" << endl;
			}
			
			break;		
		}
		case 8:
		{
			cout << ebs;
			break;
		}
		case 9:
		{
			char response;

			do
			{
				int option = display_submenu();
			
				switch(option)
				{
					case 0:
					{
						return 1;
					}
					case 1:
					{
						group temp1, temp2;
						get_groups(temp1, temp2, ebs);						

						if (temp1 > temp2)
						{
							temp1.display_name();
							cout << " has more people!" << endl;
						}

						break;		
					}
					case 2:
					{
						group temp1, temp2;
						get_groups(temp1, temp2, ebs);
						
						if (temp1 < temp2)
						{
							temp1.display_name();	
							cout << " has less people!" << endl;
						}

						break;
					}
					case 3:
					{
						group temp1, temp2;
						get_groups(temp1, temp2, ebs);
			
						if (temp1 >= temp2)
						{
							temp1.display_name();
							cout << " has more than or equal people!" << endl;
						}

						break;
					}
					case 4:
					{
						group temp1, temp2;
						get_groups(temp1, temp2, ebs);
					
						if (temp1 <= temp2)
						{
							temp1.display_name();
							cout << " has less than or equal people!" << endl;
						}

						break;
					}
					default:
					{
						return 1;
					}
				}
				
				cout << "Continue using submenu (y/n)? ";
				cin.get(response); cin.ignore();

			} while (response == 'y');	

			break;
		}
	}

	return 1;
}

int display_menu()
{
	cout << "~EMERGENCY BROADCAST SYSTEM~		" << endl
	     << "0. Exit the application     		" << endl
	     << "1. Create a group & add initial person " << endl
	     << "2. Add a person to group in EBS	" << endl
	     <<	"3. Remove a person in EBS	     	" << endl
	     << "4. Find a person in EBS		" << endl
	     << "5. Remove everyone from a group	" << endl
	     << "6. Display people in a group (EBS)	" << endl
	     << "7. Find a group and its people	        " << endl
	     << "8. Display all groups and its people   " << endl
	     << "9. Interactive EBS Stuff (Comparisons)" << endl;

	int option;
	cout << "Select an option: ";
	cin >> option; cin.ignore();
	cout << endl;

	return option; 
}

int display_submenu()
{
	cout << "~Interactive EBS Stuff~" << endl
	     << "0. Exit the submenu"	  << endl
	     << "1. Check if a group has more members than another" << endl
	     << "2. Check if a group has less members than another" << endl
	     << "3. Check if a group has more than or equal members as another" << endl
	     << "4. Check if a group has less than or equal members as another" << endl;
	
	int option;
	cout << "Select an option: ";
	cin >> option; cin.ignore();
	cout << endl;

	return option;
}

int get_groups(group & g1, group & g2, system & ebs)
{
	char one[100], two[100];
	cout << "Enter the first group name: ";
	cin.get(one, 100); cin.ignore(100, '\n');

	cout << "Enter the second group name: ";
	cin.get(two, 100); cin.ignore(100, '\n');

	int success_one = ebs.find(one, g1);
	int success_two = ebs.find(two, g2);

	if (success_one == 1 && success_two == 1)
	{
		return 1;
	}

	return 0;	
}
