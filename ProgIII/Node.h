/*
Steven Tran
CS202 | Program #3
Karla Fant
2/12/2017

This is the node header file class for the linear linked list which will
be managing a sorted list of first names for a last name group. The group class
will have a node class in order for this application to work.
*/

#ifndef PERSON
#define PERSON
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

//Top 3 ways to contact the person
//Not using a different data structure since we know size beforehand.
const int SIZE = 3;

class person
{
	public:
		person();
		~person();
		person(const person & to_copy);
	
		person & operator = (const person & src);
		//person(const char *& first, const char *& last, const char **& ways);
		//person(const char * first, const char * last);

		int add_contact_info(const char * info);
		int compare(const person & to_compare) const;
		int compare_last(const char * to_compare) const;
		int compare_first(const char * to_compare) const;
		int copy_contacts(char **& contacts) const;
		int display() const;
		int read(const char * last);

	protected:
		char * first_name;
		char * last_name;
		char * ways_to_contact[SIZE];
};

class node : public person
{
	public:
		node();
		node(const person & to_copy);
		node & operator = (const node & src);
		//node(const char *& first, const char *& last);
		//node(const char *& first, const char *& last, const char **& ways);

		node *& go_next();
		void link(node * connection);

	protected:
		node * next;
};
#endif
