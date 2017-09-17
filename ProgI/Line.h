/*
Steven Tran
CS202 | Program #1 | Portland Interactive Streetcar Map
Karla Fant
01/25/2017

This is the header file for a line which includes adding the streetcar functionality and
such. The line class is the base class for the loop and back-n-forth tracks in the Type.h
header file.
*/

#include "Node.h"
#include "Streetcar.h"
#include <fstream>
#include <cstring>

/*
A line has a stop (a node).
A node is a stop object, and the line manages the stops.
The line also has an array of streetcars (4).
*/

const int MAX = 100;

class line
{
	public:
		line();
		line(char * name);
		~line();

		//All of these functions help manage the streetcars.
		int add_streetcar(const streetcar & to_add);
		int change_streetcar_pace(char * car_name, char * pace_number);
		int display_all_cars() const;

		//Location management system.
		int verify_car_location(char * location, int option) const;
		int verify_car_name(char * name) const;
		int trace(char * name) const;

		//Service functions for streetcar system management.
		int stop_service(char * name);
		int start_service(char * name);
		bool check_service(const streetcar & car);
		bool check_service(char *car_name);
		
	protected:
		char * line_name;
		cnode * head;
		dnode * head2;

		//Line class will manage array of streetcars
		//In order to check with pacing & movement,
		//we can check every streetcar this way.
		streetcar * line_streetcars;
};
