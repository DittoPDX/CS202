/*
Steven Tran
CS202 | Program #1 | Portland Streetcar Interactive Map
Karla Fant
01/25/2017

This is the header file that manages the streetcar external properties such as
identity, service, and more. It separates the info into a location and pace because I made
a streetcar "have a" location and pace. This decreases the amount of code in a single
class instead of cramming everything into one class.
*/

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class location
{
	public:
		location();
		~location();

		//Manages data changes for location.	
		int display();
		int store_location(char * location_to_add);
		int update_location();

	protected:
		char * route_location;
};

class pace
{
	public:
		pace();
		~pace();
	
		//Manages data changes for pace.	
		int change_pace(char * to_change);	
		int change_pace(const pace &);
		int compare_pace(int given_pace);
		int display();

	protected:
		char * current_pace;
};

class streetcar
{
	public:
		streetcar(char * id, char * location, bool status, char * car_pace);
		streetcar(const streetcar &);
		streetcar(const pace &);
		streetcar();
		~streetcar();

		//Identification management which is used in Line.cpp.
		int compare(char * car_name);
		int compare_location(char * location);
		int update_location(char * location);
	
		//Flag management for DLL/NS-Line track.
		int compare_flags(const streetcar & src);
		int check_flag();
		void reverse_flag();

		//Pace management for both loop and line tracks.
		int get_pace_difference(int number);
		int update_pace(char * change_pace);
		int display_pace();
	
		//Service info for user management.	
		void update_service();		
		int get_service_info() const;

		//Standard information management.
		int display_info();
		int display_location();

		//Operator overloading used for certain checks in line classes.
		streetcar & operator = (const streetcar & src);
		bool operator ! () const;
		bool operator != (const streetcar & src);
		bool operator == (const streetcar & src);

	private:
		//"Has a" relationships.
		location streetcar_location;
		pace streetcar_pace;

		char * identity;
		char * current_location;
		bool current_status;
		bool flag;
};
