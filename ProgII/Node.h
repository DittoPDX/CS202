/*
Steven Tran
CS 202 | Program #2 : Dynamic Binding & Transit
Karla Fant
2/01/2017

This is the header file for the node implementation which is used for
the Linear Linked List data structure. This data structure should manage
the popularity pointed to.
*/

#ifndef POPULARITY
#define POPULARITY

#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>

using namespace std;

class popularity
{
	public:
		popularity();
		popularity(const char *& to_copy);
		popularity(const popularity & to_copy);
		~popularity();

		void display() const;
		void display_status() const;
		int compare(const char *& to_compare) const;
		int retrieve_info(char *& to_compare, bool & check_status) const;
		int verify_info(const char * to_verify) const;

	protected:
		char * busy_info;
		bool status;
};

class node : public popularity
{
	public:
		node(const char *& busy_info);
		node(const popularity & to_copy);
		
		node *& go_next();
		void link(node * connection);

	protected:
		node * next;
};
#endif

