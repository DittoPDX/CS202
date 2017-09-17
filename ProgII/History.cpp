/*
Steven Tran
CS 202 | Program #2
Karla Fant
2/02/2017

This is the implementation file for the rider history header file. This entire file implements
the linear linked list functions along with the array of M riding experience functions which
manipulate the data. This is technically a "Stack" which uses an index to manage the array
indices. Each node2 is essentially a rider history which is an array of M riding experiences.
*/

#include "History.h"

using namespace ride_collection;

rider::rider() : head(NULL), top_index(0)
{

};

rider::~rider()
{
	if (head)
	{
		clear_all(head);
	}
}

rider::rider(const rider & src)
{
	copy_LLL(head, src.head);
}

//Copy constructor for linear linked lists with array of M riding experiences.
void rider::copy_LLL(node2 *& dest, node2 * src)
{
	if (!src)
	{
		dest = NULL;
		return;
	}
	else
	{
		dest = new node2(*src);
		return copy_LLL(dest -> go_next(), src -> go_next());
	}
}

void rider::clear_all(node2 *& head)
{
	if (!head)
	{
		return;
	}

	clear_all(head -> go_next());

	delete head;
	head = NULL;
}

//Adds an experience a log of 5 for each node2.
int rider::add(const char * to_add)
{
	node2 * temp = head;

	if (!head)
	{
		head = new node2();
		head -> add(to_add);
		head -> link(NULL);
		++top_index;	
		return 1;
	}
	
	if (top_index == SIZE)
	{
		top_index = 0;
		temp = head;
		head = new node2();
		head -> add(to_add);
		head -> link(temp);
		++top_index;
	}	
	else
	{
		head -> add(to_add);
		++top_index;
	}

	return 1;
}

//Removes each individual log of 5 experiences.
int rider::remove()
{
	if (!head)
	{
		return 0;
	}

	node2 * temp = head -> go_next();
	head -> remove();
	delete head;	
	head = temp;
	top_index = SIZE;
	
	return 1;
}

int rider::remove_all()
{
	if (!head)
	{
		return 0;
	}

	int value = remove_all(head);

	return 1 + value;
}

int rider::remove_all(node2 *& head)
{
	if (!head)
	{
		return 1;
	}

	node2 * temp = head -> go_next();
	head -> remove();
	delete head;
	head = temp;
	top_index = 0;

	return remove_all(head);
}

int rider::retrieve(char *& to_retrieve)
{
	if (!head)
	{
		return 0;
	}

	return retrieve(head, to_retrieve);
}

int rider::retrieve(node2 * head, char *& to_retrieve)
{
	if (!head)
	{
		return 0;
	}

	if (head -> retrieve_info(to_retrieve) == 1)
	{
		return 1;
	}

	return retrieve(head -> go_next(), to_retrieve);
}

void rider::display() const
{
	if (!head)
	{
		return;
	}


	return display(head);
}

void rider::display(node2 * head) const
{
	if (!head)
	{
		return;
	}

	head -> display();

	return display(head -> go_next());
}

void rider::display_recent() const
{
	if (!head)
	{
		return;
	}

	head -> display_recent();
}

history::history() : ride_history(NULL), index(0)
{
	ride_history = new char * [SIZE];

	for (int i = 0; i < SIZE; ++i)
	{
		ride_history[i] = NULL;
	}

	index = 0;
}

history::history(const char **& to_copy)
{
	for (int i = 0; i < SIZE; ++i)
	{
		ride_history[i] = new char[strlen(to_copy[i]) + 1];
		strcpy(ride_history[i], to_copy[i]);
	}
}

history::history(const history & to_copy)
{
	for (int i = 0; i < SIZE; ++i)
	{
		ride_history[i] = new char[strlen(to_copy.ride_history[i]) + 1];
		strcpy(ride_history[i], to_copy.ride_history[i]);
	}
}

history::~history()
{
	for (int i = 0; i < SIZE; ++i)
	{
		if (ride_history)
		{
			delete [] ride_history[i];
			ride_history[i] = NULL;
		}
	}
	
	delete [] ride_history;
}

void history::display() const
{
	for (int i = 4; i >= 0; --i)
	{	
		if (ride_history[i])
		{
			cout << ride_history[i] << endl;
		}
		
		if (i == 0)
		{
			cout << "---------------------------------" << endl;
		}
	}
}

//The most recent riding experiences
//can be accessed without traversal.
void history::display_recent() const
{
	if (!ride_history[0])
	{
		return;
	}

	for (int i = 0; i < SIZE; ++i)
	{
		/*
		if (i == SIZE - 1)
		{
			cout << ride_history[i] << endl;
		}

		if (!ride_history[i + 1])
		{
			cout << ride_history[i] << endl;
			return;
		}
		*/
		if (ride_history[i])
		{
			cout << ride_history[i] << endl;
		}
	}
}

void history::add(const char *& to_add)
{
	for (int i = 0; i < SIZE; ++i)
	{
		if (!ride_history[i])
		{
			ride_history[i] = new char[strlen(to_add) + 1];
			strcpy(ride_history[i], to_add);
			return;
		}
	} 
} 

void history::remove()
{
	for (int i = 0; i < SIZE; ++i)
	{
		delete [] ride_history[i];
		ride_history[i] = NULL;
	}
}

int history::retrieve_info(char *& to_compare) const
{
	int size = (unsigned)strlen(to_compare);

	for (int i = 0; i < SIZE; ++i)
	{		
		if (!ride_history[i])
		{
			return -1;	
		}

		if (strncmp(to_compare, ride_history[i], size) == 0 && ride_history != NULL)
		{
			to_compare = new char[strlen(ride_history[i]) + 1];
			strcpy(to_compare, ride_history[i]);
			return 1;
		}
	}

	return 0;
}

node2::node2(const char **& ride_history) : history(ride_history)
{

}

node2::node2(const history & to_copy) : history(to_copy)
{

}

node2::node2() : history()
{

}

node2 *& node2::go_next()
{
	return next;
}

void node2::link(node2 * connection)
{
	next = connection;
}
