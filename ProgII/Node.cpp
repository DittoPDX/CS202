/*
Steven Tran
CS202 | Program #2
Karla Fant
2/02/2017

This is the implementation file for the popularity header file. Each node "is a" popularity which can 
access the data popularity has directly, and this follows OOP. By using this hierarchy, it reduces
the amount of getters and setters as opposed to popularity "is a" node.
*/

#include "Node.h"

popularity::popularity() : busy_info(NULL), status(false)
{

}

popularity::popularity(const char *& to_copy)
{
	busy_info = new char[strlen(to_copy) + 1];
	strcpy(busy_info, to_copy);

	//Randomized status instead of manually setting each status.
	status = rand()&1;
}

popularity::popularity(const popularity & to_copy)
{
	busy_info = new char[strlen(to_copy.busy_info) + 1];
	strcpy(busy_info, to_copy.busy_info);

	status = rand()&1;
}

popularity::~popularity()
{
	if (busy_info)
	{
		delete [] busy_info;
		busy_info = NULL;
	}
}

void popularity::display() const
{
	if (busy_info)
	{
		cout << busy_info << " : ";
		display_status();
	}
}

void popularity::display_status() const
{
	(status == true) ? cout << "In-Service" << endl : cout << "Not-In-Service" << endl;
}

int popularity::compare(const char *& to_compare) const
{
	return strcmp(busy_info, to_compare);	
}

int popularity::retrieve_info(char *& to_compare, bool & check_status) const
{
	int size = (unsigned)strlen(to_compare);

	if (strncmp(to_compare, busy_info, size) == 0)
	{
		to_compare = new char[strlen(busy_info) + 1];
		strcpy(to_compare, busy_info);
		check_status = status;
		return 1;
	}
	
	return 0;
}

int popularity::verify_info(const char * to_verify) const
{
	int size = (unsigned)strlen(to_verify);

	if (strncmp(to_verify, busy_info, size) == 0)
	{
		return 1;
	}

	return 0;
}

/***********************************************************/
//This is the node implementation for the Linear Linked Lists.

node::node(const char *& busy_info) : popularity(busy_info)
{
	
}

node::node(const popularity & to_copy) : popularity(to_copy)
{

}

node *& node::go_next()
{
	return next;
}

void node::link(node * connection)
{
	next = connection;
}
