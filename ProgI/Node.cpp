/*
Steven Tran
CS202 | Program #1 | Portland Streetcar Interactie Map
Karla Fant
01/25/2017

This is the implementation .cpp file for the Node.h header file. The function 
implementations below work with how we can traverse certain linked lists without
violating OOP rules.
*/

#include "Node.h"

//Default constructor so that Map.h could "have" a stop.
stop::stop() : stop_name(NULL)
{

}

//Constructor to copy data inside args to protected data member.
stop::stop(const char * stop_data) : stop_name(NULL)
{
	if (stop_name)
	{
		stop_name = NULL;
	}
	else
	{
		stop_name = new char[strlen(stop_data) + 1];
		strcpy(stop_name, stop_data);
	}	
}

//Constructor to copy stop object inside args to protected data member.
stop::stop(const stop & stop_data) : stop_name(NULL)
{
	stop_name = new char[strlen(stop_data.stop_name) + 1];
	strcpy(stop_name, stop_data.stop_name);

}

//Operator overloading to copy arg object to current object.
stop & stop::operator = (const stop & src)
{
	if (this == &src)
	{
		return *this;
	}

	delete [] stop_name;
	stop_name = new char[strlen(src.stop_name) + 1];
	strcpy(stop_name, src.stop_name);

	return *this;
}

//Operator overloading to check if data member is NULL or not.
bool stop::operator !()
{
	return (!stop_name);
}

stop::~stop()
{
	if (stop_name)
	{
		delete [] stop_name;
		stop_name = NULL;
	}
}

int stop::compare(char * to_compare)
{
	return strcmp(to_compare, stop_name);
}

int stop::compare(const stop & to_compare)
{
	return strcmp(stop_name, to_compare.stop_name);
}

//Display stop data
void stop::display() const
{
	if (stop_name)
	{
		cout << stop_name << endl;
	}
}

//Node copies char * stop data.
cnode::cnode(const char * stop_data) : stop(stop_data)
{
	
}

//Node copies stop object.
cnode::cnode(const stop & stop_data) : stop(stop_data)
{
	
}

char * cnode::get_stop()
{
	return stop::stop_name;
}

cnode *& cnode::go_next()
{
	return next;		
}

void cnode::link(cnode * connection)
{
	next = connection;
}

char * dnode::get_stop()
{
	return stop::stop_name;
}

//Node copies char * stop data.
dnode::dnode(const char * stop_data) : stop(stop_data)
{

}

//Node copies stop object.
dnode::dnode(const stop & stop_data) : stop(stop_data)
{

}

dnode *& dnode::go_next()
{
	return next;
}

dnode *& dnode::go_prev()
{
	return previous;
}

void dnode::link_next(dnode * connection)
{
	next = connection;
}

void dnode::link_prev(dnode * connection2)
{
	previous = connection2;
}
