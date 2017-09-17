/*
Steven Tran
CS202 | Program #2
Karla Fant
2/02/2017

This is the implementatin file for the transit types. Overall, the transit implementation file
contains a few virtual functions for common use within the derives classes. The transit class
should not be able to create its own object since its an abstract base class.
*/

#include "Transit.h"

transit::transit() : head(NULL), tail(NULL)
{

}

//Copy constructor
transit::transit(const transit & src) : rider(src)
{
	copy_LLL(head, src.head);
}

//Recursive function for the copy constructor.
void transit::copy_LLL(node *& dest, node * src)
{
	if (!src)
	{
		dest = NULL;
		return;
	}
	else
	{
		dest = new node(*src);
		dest -> link(NULL);
		return copy_LLL(dest -> go_next(), src -> go_next());
	}
}

transit::~transit()
{
	if (head)
	{
		clear_all(head);
	}
}

//Recursive function to clear all of the nodes in an LLL.
void transit::clear_all(node *& head)
{
	if (!head)
	{
		return;
	}

	clear_all(head -> go_next());

	delete head;
	head = NULL;
}

//Add a time slot with popularity info.
int transit::add_popularity(const char * info)
{
	if (!info)
	{
		return 0;
	}

	if (!head)
	{
		head = new node(info);
		head -> link(NULL);
		tail = head;
	}
	else
	{
		return add_popularity(head, info);
	}

	return 1;
}

//Recursive function for adding a time slot.
int transit::add_popularity(node *& head, const char * info)
{
	if (!head)
	{
		return 0;
	}
	else
	{
		tail -> go_next() = new node(info);
		tail = tail -> go_next();
		tail -> link(NULL);
		return 1;	
	}

	return add_popularity(head -> go_next(), info);
}

//Remove a time slot with popularity info.
int transit::remove_popularity(const char * info)
{
	if (!head || !info)
	{
		return 0;
	}

	return remove_popularity(head, info);
}

//Recursive function for removing a time slot.
int transit::remove_popularity(node *& head, const char * info)
{
	if (!head)
	{
		return 0;
	}

	/*
	if (head -> compare(info) == 0)
	{
		delete head;
		head = NULL;
		return 1;
	}
	*/

	if (head -> verify_info(info) == 1)
	{
		node * temp = head -> go_next();
		delete head;
		head = NULL;
		head = temp;
		return 1;
	}

	return remove_popularity(head -> go_next(), info);
}

//Removes all popularity time slots.
int transit::remove_all_popularity()
{
	if (!head)
	{
		return 0;
	}

	return remove_all_popularity(head);
}

//Recursive function for removing all time slots.
int transit::remove_all_popularity(node *& head)
{
	if (!head)
	{
		return 0;
	}

	int items = remove_all_popularity(head -> go_next()) + 1;

	delete head;
	head = NULL;
	return items;
}

//Retrieves a time slot with occupation information.
int transit::retrieve_popularity(char *& to_retrieve, bool & check_status)
{
	if (!head || !to_retrieve)
	{
		return 0;
	}

	//Tail pointer used to retrieve for efficiency.
	if (tail -> retrieve_info(to_retrieve, check_status) == 1)
	{
		return 1;
	}

	return retrieve_popularity(head, to_retrieve, check_status);
}

//Recursive function to retrieve a time slot with occupation info.
int transit::retrieve_popularity(node * head, char *& to_retrieve, bool & check_status)
{
	if (!head)
	{
		return 0;
	}

	if (head -> retrieve_info(to_retrieve, check_status) == 1)
	{
		return 1;
	}

	return retrieve_popularity(head -> go_next(), to_retrieve, check_status);
}

//Load an external file containing popularity occupation info.
int transit::load(const char file[])
{
	if (!file)
	{
		return 0;
	}

	ifstream file_in;
	file_in.open(file);
	char transit_data[MAX];

	if (file_in.is_open())
	{
		while (!file_in.eof())
		{
			if (file_in.peek() == -1)
			{
				return 1;
			}

			file_in.get(transit_data, MAX, '*');
			file_in.ignore(MAX, '\n');

			int check_add = add_popularity(transit_data);

			if (check_add == 0)
			{
				cout << "Error reading file." << endl;
			}
		}
	}

	return 1;
}

streetcar::streetcar() : streetcar_fee(0)
{

}

streetcar::~streetcar()
{

}

void streetcar::cost()
{
	cout << "~Fare Options~" << endl
	     << "1) 1 Day = $2.00" << endl
	     << "2) 1 Month = $40.00" << endl
	     << "3) 1 Year = $440.00" << endl << endl;
}

int streetcar::display() const
{
	if (!head)
	{
		return 0;
	}	

	return display(head);	
}

int streetcar::display(node * head) const
{
	if (!head)
	{
		return 1;
	}
	else
	{
		head -> display();
	}

	return display(head -> go_next());
}

bus::bus() : bus_fee(0)
{

}

bus::~bus()
{

}

void bus::cost()
{
	cout << "~Fare Options~" << endl
	     << "2.5 Hour Ticket: $2.50" << endl
 	     << "1-Day Pass: $5.00     " << endl
	     << "7-Day Pass: $26.00    " << endl
	     << "14-Day Pass: $51.00   " << endl
	     << "30-Day Pass: $100     " << endl << endl;
}

int bus::display() const
{
	if (!head)
	{
		return 0;
	}

	return display(head);
}

int bus::display(node * head) const
{
	if (!head)
	{
		return 1;
	}
	else
	{
		head -> display();
	}

	return display(head -> go_next());
}

max_train::max_train() : max_fee(0)
{

}

max_train::~max_train()
{

}

void max_train::cost()
{
	cout << "~Fare Options~" << endl
	     << "2.5 Hour Ticket: $2.50" << endl
 	     << "1-Day Pass: $5.00     " << endl
	     << "7-Day Pass: $26.00    " << endl
	     << "14-Day Pass: $51.00   " << endl
	     << "30-Day Pass: $100     " << endl << endl;
}

int max_train::display() const
{
	if (!head)
	{
		return 0;
	}

	return display(head);
}

int max_train::display(node * head) const
{
	if (!head)
	{
		return 1;
	}
	else
	{
		head -> display();
	}

	return display(head -> go_next());
}
