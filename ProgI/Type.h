/*
Steven Tran
CS202 | Program #1 | Portland Streetcar Interactive Map
Karla Fant
01/25/2017

This is the header file which contains the two different line classes, a loop and a line.
Also, this is where the logic is implemented for managing streetcar pacing, streetcar
adding, and streetcar locating/tracing. The loop is a CLL, and the line is a DLL.

The most important part of the DLL is that two streetcars can temporary be at an end stop
after switching directions. These types inherit the "line" class, so they are both able to
check if streetcars are available etc.
*/

#include "Line.h"

//This is the CLL.
class loop: public line
{
	public:
		loop(char * name);
		loop();
		~loop();

		//Loading, adding, and displaying streetcar stops.
		int load(const char file []);
		int add_stop(char * stop_name);	
		int display_stops() const;

		//Pacing public functions to be put into main.
		int verify_car_location(char * location) const;	
		int run_streetcar(char * car_name);
		int check_pacing(streetcar & pace_check);

	protected:	
		
		//Mostly recursive helper functions for managing pace.
		int calculate_pace_distance(cnode * head, char * location_one, char * location_two);
		int cpd(cnode * head, char * location_two);
		void clear_all(cnode *& head);
		int compare_location(cnode * head, streetcar & to_update) const;
		int display_stops(cnode * head) const;
		cnode * obtain_location(cnode * head, streetcar & pace_check);
		int verify_car_location(cnode * head, char * location) const;

};

//This is the DLL.
class nsline: public line
{
	public:
		nsline(char * name);
		nsline();
		~nsline();

		//Loading, adding, and displaying streetcar stops.
		int load(const char file []);
		int add_stop(char * stop_name);
		int display_stops() const;
	
		//Pacing public functions to be put into main.
		int verify_car_location(char * location) const;
		int run_streetcar(char * car_name);
		int check_pacing(streetcar & pace_check);

	protected:
		
		//Mostly recursive helper functions for managing pace.
		int add_stop(dnode *& head2, char * stop_name);
		void clear_all(dnode *& head2);
		int display_stops(dnode * head2) const;
		int verify_car_location(dnode * head2, char * location) const;
		int compare_location(dnode * head2, streetcar & to_update) const;
		int compare_location2(dnode * head2, streetcar & to_update) const;

		//These functions calculate the distances between two streetcars.
		dnode * obtain_location(dnode * head2, streetcar & pace_check);
		int calculate_pace_distance(dnode * head2, char * location_one, char * location_two);
		int cpd(dnode * head2, char * location_two);

		int calculate_pace_distance2(dnode * head2, char * location_one, char * location_two);
		int cpd2(dnode * head2, char * location_two);	
};
