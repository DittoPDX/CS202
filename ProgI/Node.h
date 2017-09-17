/*
Steven Tran
CS202 | Program #1 | Portland Streetcar Interactive Map
Karla Fant
01/25/2017

This is the header file which contains the function protoypes for a circular linked list,
doubly linked list, and stop classes. A node "is a" stop plus the pointer to manage every
proceding stop. The node class can follow object oriented programming rules and allow
client direct access to stop's functionality without implementing stop in the node class.
*/

//Guard code to allow multiple .h includes.
#ifndef STREETCAR_STOP
#define STREETCAR_STOP

#include <iostream>
#include <cctype>
#include <cstring>

using namespace std;

class stop
{
	public:
		stop();
		stop(const char * stop_data);
		stop(const stop &);
		~stop();

		//Operator overloading to support the conditionals in Map.cpp.
		stop & operator = (const stop &);	
		bool operator ! ();

		//Functions for comparing and displaying.
		void display() const;
		int compare(char * to_compare);
		int compare(const stop & to_compare);

	protected:
		char * stop_name;
};

//Circular Linked List functions and data members.
class cnode: public stop
{
	public:
		cnode(const char * stop_data);
		cnode(const stop &);
		char * get_stop();

		cnode *& go_next();
		void link(cnode * connection);

	protected:
		cnode * next;		
};

//Doubly Linked List functions and data members.
class dnode: public stop
{
	public:
		dnode(const char * stop_data);
		dnode(const stop &);
		char * get_stop();

		dnode *& go_next();
		dnode *& go_prev();
		void link_next(dnode * connection);
		void link_prev(dnode * connection2);

	protected:
		dnode * next;
		dnode * previous;
};

#endif
