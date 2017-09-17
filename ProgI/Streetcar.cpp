/*
Steven Tran
CS202 | Program #1 | Portland Streetcar Interactive Map
Karla Fant
01/25/2017

This is the implementation file for the Streetcar, Location, and Pace classes. These
implementations create the external properties of a streetcar, and this information
is pushed up towards the line classes.
*/

#include "Streetcar.h"

//Default constructor with initialization list for location.
location::location() : route_location(NULL)
{
		
}

//Destructor to delete location data.
location::~location()
{
	if (route_location)
	{
		delete [] route_location;
		route_location = NULL;
	}
}

//Displays the current location.
int location::display()
{
	if (!route_location)
	{
		return 0;
	}

	cout << "Current location is: " << route_location << endl;

	return 1;
}

//Stores the location.
int location::store_location(char * location_to_add)
{
	if (!location_to_add)
	{
		return 0;
	}

	route_location = new char[strlen(location_to_add) + 1];
	strcpy(route_location, location_to_add);

	return 1;
}

//Default constructor with initialization list.
pace::pace() : current_pace(NULL)
{

}

//Destructor to remove pace data.
pace::~pace()
{
	if (current_pace)
	{
		delete [] current_pace;
		current_pace = NULL;	
	}
}

//Changes the pace.
int pace::change_pace(const pace & src)
{
	if (!src.current_pace)
	{
		return 0;
	}

	current_pace = new char[strlen(src.current_pace) + 1];
	strcpy(current_pace, src.current_pace);
	src.~pace();
	
	return 1;
}

//Compares the pace for calculations in Type.cpp.
int pace::compare_pace(int given_pace)
{
	if (given_pace == 0)
	{
		return 0;
	}

	int set_pace = atoi(current_pace);

	if (given_pace <= set_pace)
	{
		return -2;
	}
	else
	{
		return -1;
	}
}

//Changes pace with char passed into it.
int pace::change_pace(char * to_change)
{
	if (!current_pace)
	{
		current_pace = new char[strlen(to_change) + 1];
	}

	int temp = atoi(to_change);

	if (temp <= 0)
	{
		cout << "Pace cannot be negative." << endl;
		return -1;
	}

	if (current_pace)
	{
		delete [] current_pace;
	}

	current_pace = new char[strlen(to_change) + 1];
	strcpy(current_pace, to_change);

	return 1;
}

//Displays the streetcar's current pace.
int pace::display()
{
	if (!current_pace)
	{
		return 0;
	}

	cout << "Streetcar's pace is: " << *current_pace << endl;
	return 1;
}

//Constructor that initializes data members to what user inputs.
streetcar::streetcar(char * id, char * location, bool status, char * car_pace) : flag(false)
{
	identity = new char[strlen(id) + 1];
	strcpy(identity, id);

	current_location = new char[strlen(location) + 1];
	strcpy(current_location, location);
	
	current_status = status;

	streetcar_pace.change_pace(car_pace);
}

//Copying data from previous object.
streetcar::streetcar(const streetcar & src) : current_status(src.current_status)
{
	identity = new char[strlen(src.identity) + 1];
	strcpy(identity, src.identity);

	current_location = new char[strlen(src.current_location) + 1];
	strcpy(current_location, src.current_location);	
}

//Default constructor for initializing all members to NULL.
streetcar::streetcar() : identity(NULL), current_location(NULL), current_status(false), flag(false)
{
		
}

//Destructor to remove data.
streetcar::~streetcar()
{
	if (identity)
	{
		delete [] identity;
		identity = NULL;
	}
	if (current_location)
	{
		delete [] current_location;
		current_location = NULL;
	}
}

//Compare and pace functions used in Type.cpp function implementations with
//data structures.
int streetcar::compare(char * car_name)
{
	return strcmp(car_name, identity);
}

int streetcar::compare_location(char * location)
{
	if (!location || !current_location)
	{
		return -1;
	}

	return strcmp(location, current_location);
}

int streetcar::get_pace_difference(int number)
{
	int check = streetcar_pace.compare_pace(number);
	return check;
}

//Updates the pace of a streetcar.
int streetcar::update_pace(char * pace_change)
{
	if (!pace_change)
	{
		return 0;
	}

	streetcar_pace.change_pace(pace_change);
	streetcar_pace.display();

	return 1;
}

//Gets the service availability of a streetcar.
int streetcar::get_service_info() const
{
	if (current_status == true)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//Change the flag for streetcar service.
void streetcar::update_service()
{
	current_status = !current_status;
}

//Display all of the streetcar's information.
int streetcar::display_info()
{
	if (!identity && !current_location)
	{
		return 0;
	}	

	cout << "Streetcar Identification: " << identity << endl;
	streetcar_location.display();
	
	if (!current_status)
	{
		cout << "Streetcar not in service." << endl;
	}	
	else
	{
		cout << "Streetcar in service." << endl;
	}

	cout << "Streetcar current pace: ";
	streetcar_pace.display();
	cout << "-------------------------------------------------------" << endl;

	return 1;
}

int streetcar::display_location()
{
	int success = streetcar_location.display();
	return success;
}

int streetcar::display_pace()
{
	int success = streetcar_pace.display();
	return success;
}

//Compare the flags for directions (DLL).
int streetcar::compare_flags(const streetcar & src)
{
	if (flag == src.flag)
	{
		return 1000;
	}
	else
	{
		return -1000;
	}
}

//Check the flags for managing directions.
int streetcar::check_flag()
{
	if (flag == true)
	{
		return 1000;
	}
	else
	{
		return -1000;
	}
}

//Reverse flag if a streetcar on a DLL changes direction.
void streetcar::reverse_flag()
{
	flag = !flag;
}

//Update the location of a current streetcar.
int streetcar::update_location(char * location)
{
	if (!location)
	{
		return 0;
	}	

	//streetcar_location.~location();
	if (!current_location)
	{
		current_location = new char[strlen(location) + 1];
	}

	if (current_location)
	{
		delete [] current_location;
	}

	current_location = new char[strlen(location) + 1];
	strcpy(current_location, location);
	streetcar_location.~location();

	int location_status = streetcar_location.store_location(location);

	return location_status;
}

//Copy constructor for a streetcar.
streetcar & streetcar::operator = (const streetcar & src)
{
	if (this == & src)
	{
		return * this;
	}

	if (identity)
	{
		delete [] identity;
		identity = NULL;
	}
	if (current_location)
	{
		delete [] current_location;
	}

	identity = new char[strlen(src.identity) + 1];
	strcpy(identity, src.identity);

	current_location = new char[strlen(src.current_location) + 1];
	strcpy(current_location, src.current_location);	

	streetcar_location.store_location(src.current_location);	
		
	current_status = src.current_status;
		
	streetcar_pace.change_pace(src.streetcar_pace);

	flag = src.flag;

	return * this;
}

//Overloading the not operator to see if a streetcar is NULL.
bool streetcar::operator !() const
{
	if (!current_location && !identity)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Operator overloading for comparing streetcar identities.
bool streetcar::operator != (const streetcar & src) 
{
	return identity != src.identity;
}

//Operator overloading for checking streetcar identities.
bool streetcar::operator == (const streetcar & src)
{
	return identity == src.identity;
}
