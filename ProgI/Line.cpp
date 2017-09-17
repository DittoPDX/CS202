/*
Steven Tran
CS202 | Program #1 | Portland Streetcar Interactive Map
Karla Fant
01/25/2017

My map has the following settings:
-2 lines (A-Loop/NS Line)
-4 streetcars PER line
-Controller should be able to control pace of ANY streetcar
	-should be able to LOCATE/TRACE ANY streetcar
	-take a streetcar out of service

This .cpp implementation file allows for basic management of streetcars such as
adding it and taking it out of service.
*/

#include "Line.h"

//Default constructor with initialization list.
line::line() : line_name(NULL), head(NULL), head2(NULL), line_streetcars(NULL)
{
	
}

//Constructor that sets the name of the line.
line::line(char * name) : line_name(NULL), head(NULL), head2(NULL), line_streetcars(NULL)
{
	//Copy user data to private data
	line_name = new char[strlen(name) + 1];
	strcpy(line_name, name);

	//Allocate memory for 4 total streetcars.
	//Max streetcars available on a line is 4.
	line_streetcars = new streetcar[4];
}

//Destructor to clear line data.
line::~line()
{
	if (line_streetcars)
	{
		delete [] line_streetcars;
	}

	if (line_name)
	{
		delete [] line_name;
		line_name = NULL;
	}
}

//Adds a streetcar to the array.
int line::add_streetcar(const streetcar & to_add)
{
	for (int i = 0; i < 4; ++i)
	{	
		if (!line_streetcars[i])
		{
			line_streetcars[i] = to_add;	
			return 1;
		}
	}	

	return 0;
}

//Change the streetcar pace through searching in an array.
int line::change_streetcar_pace(char * car_name, char * pace_number)
{
	for (int i = 0; i < 4; ++i)
	{
		if (!line_streetcars[i])
		{
			return -1;
		}

		if (line_streetcars[i].compare(car_name) == 0)
		{
			line_streetcars[i].update_pace(pace_number);
			//line_streetcars[i].display_pace();
			return 1;
		}
	}

	return 0;
}

//Display all of the streetcars.
int line::display_all_cars() const
{
	for (int i = 0; i < 4; ++i)
	{
		if (!line_streetcars[i])
		{
			return 0;
		}

		line_streetcars[i].display_info();
	}

	return 1;
}

//Verify car name for multiple purposes like taking it out of service.
int line::verify_car_name(char * name) const
{
	if (!name)
	{
		return 0;
	}

	//Iterates through the entire array to find correct streetcar.
	for (int i = 0; i < 4; ++i)
	{
		if (!line_streetcars[0])
		{
			return -2;
		}

		if (!line_streetcars[i])
		{
			return -1;
		}

		if (line_streetcars[i].compare(name) == 0)
		{
			return 1;
		}
	}

	return 0;
}

//Stops the service of a streetcar by searching for its name.
int line::stop_service(char * name)
{
	if (!name)
	{
		return 0;
	}		

	//Iterates through entire array to get correct streetcar.
	for (int i = 0; i < 4; ++i)
	{
		if (!line_streetcars[i])
		{
			return 0;
		}

		if (line_streetcars[i].compare(name) == 0)
		{
			if (line_streetcars[i].get_service_info() == false)
			{
				cout << "Streetcar is already not in service." << endl;
				return -2;
			}	
			else
			{
				cout << "Streetcar is no longer running." << endl;
				line_streetcars[i].update_service();
				return 1;
			}
		}	
	}

	return 0;
}

//Starts the service of streetcar by searching for its name.
int line::start_service(char * name)
{
	if (!name)
	{
		return 0;
	}

	//Iterates through entire array to get correct streetcar.
	for (int i = 0; i < 4; ++i)
	{
		if (!line_streetcars[i])
		{
			return 0;
		}

		if (line_streetcars[i].compare(name) == 0)
		{
			if (line_streetcars[i].get_service_info() == true)
			{
				cout << "Streetcar is already in service." << endl;
				return -2;
			}
			else
			{
				cout << "Streetcar is now in service!" << endl;
				line_streetcars[i].update_service();
				return 1;
			}
		}
	}
	
	return 0;
}

//Check status will be a helper function for both the run and pacing.
bool line::check_service(const streetcar & car)
{
	int check = car.get_service_info();

	if (check == 1)
	{
		return true;
	}	
	else
	{
		return false;
	}
}

//Calls the check service function above for verifying service.
bool line::check_service(char * car_name)
{
	if (!car_name)
	{
		return false;
	}

	//Iterates through entire array to get correct streetcar.
	for (int i = 0; i < 4; ++i)
	{
		if (!line_streetcars[i])
		{
			return false;
		}

		if (line_streetcars[i].compare(car_name) == 0 && check_service(line_streetcars[i]) == true)
		{
			return true;	
		}
	}

	return false;
}

//Allows the user to trace for a streetcar.
int line::trace(char * name) const
{
	if (!name)
	{
		return 0;
	}

	//Iterates through entire array to get correct streetcar.
	for (int i = 0; i < 4; ++i)
	{
		if (!line_streetcars[i])
		{
			return 0;
		}

		if (line_streetcars[i].compare(name) == 0)
		{
			line_streetcars[i].display_info();
			return 1;
		}
	}

	return 0;
}
