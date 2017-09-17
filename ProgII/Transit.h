/*
Steven Tran
CS202 | Program #2
Karla Fant
2/01/2017

This is the header file for the transit abstract base class along with its derived classes.
The base class has all of the data structure functions which the derived classes inherit. In terms of
OOP principles, the base is getting all of the data pushed up.
*/

#ifndef TRANSIT
#define TRANSIT

#include <iostream>
#include <cctype>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Node.h"
#include "History.h"

using namespace std;
using namespace ride_collection;

static const int MAX = 2500;

class transit : public rider
{
	public:
		transit();
		transit(const transit & src);

		int add_popularity(const char * info);
		/*
		Although I have implemented the remove functions
		for transit popularity data, they shouldn't be
		available for program use since it wouldn't
		make sense for a user to remove a time off
		a transit schedule system. Oh well.
		*/
		int remove_popularity(const char * info);
		int remove_all_popularity();
		int retrieve_popularity(char *& to_retrieve, bool & check_status);
		int load(const char file[]);

		virtual ~transit();
		
		//Cost is a different method which is resolved through the derived classes.
		virtual void cost() = 0;
		virtual int display() const = 0;
	
	protected:
		rider transit_rider;
		node * head;
		node * tail;

		void clear_all(node *& head);
		void copy_LLL(node *& dest, node * src);
		int add_popularity(node *& head, const char * info);
		int remove_popularity(node *& head, const char * info);
		int remove_all_popularity(node *& head);
		int retrieve_popularity(node * head, char *& to_retrieve, bool & check_status);

};

class streetcar : public transit
{
	public:
		streetcar();	
		~streetcar();

		void cost();
		int display() const;

	protected:
		double streetcar_fee;
		int display(node * head) const;
};

class bus : public transit
{
	public:
		bus();
		~bus();

		void cost();
		int display() const;

	protected:
		double bus_fee;
		int display(node * head) const;
};

class max_train : public transit
{
	public:
		max_train();
		~max_train();

		void cost();
		int display() const;

	protected:
		double max_fee;
		int display(node * head) const;
};
#endif
