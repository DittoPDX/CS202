/*
Steven Tran
CS202 | Program #3
Karla Fant
2/12/2017

This is the .cpp file which contains the function implementations for the person
and node class. The node is derived from a person, so it's literally a person which
makes it a lot easier for the "Group" class to manage the people inside while
keeping the first names sorted.
*/

#include "Node.h"

//Constructor to initialize every data member of person to 0.
person::person() : first_name(NULL), last_name(NULL)
{
	for (int i = 0; i < SIZE; ++i)
	{
		ways_to_contact[i] = NULL;
	}
}

//Destructor to clear all dynamic memory for person.
person::~person()
{
	if (first_name)
	{
		delete [] first_name;
	}

	if (last_name)
	{
		delete [] last_name;
	}
	
	for (int i = 0; i < SIZE; ++i)
	{
		if (ways_to_contact[i])
		{
			delete [] ways_to_contact[i];
		}
	}
}

//Copy constructor to create a new person object.
person::person(const person & to_copy)
{
	first_name = new char[strlen(to_copy.first_name) + 1];
	strcpy(first_name, to_copy.first_name);

	last_name = new char[strlen(to_copy.last_name) + 1];
	strcpy(last_name, to_copy.last_name);

	for (int i = 0; i < SIZE; ++i)
	{
		if (to_copy.ways_to_contact[i])
		{
			ways_to_contact[i] = new char[strlen(to_copy.ways_to_contact[i]) + 1];
			strcpy(ways_to_contact[i], to_copy.ways_to_contact[i]);
		}
	}	
}

//Assignment operator because there's dynamic data and copy constructor.
person & person::operator = (const person & src)
{
	if (this == &src) return * this;

	if (last_name)
	{
		delete [] last_name;
	}
	
	if (first_name)
	{
		delete [] first_name;
	}

	for (int i = 0; i < SIZE; ++i)
	{
		if (ways_to_contact[i])
		{
			delete [] ways_to_contact[i];
		}
	}

	for (int i = 0; i < SIZE; ++i)
	{
		if (src.ways_to_contact[i])
		{
			ways_to_contact[i] = new char[strlen(src.ways_to_contact[i]) + 1];
			strcpy(ways_to_contact[i], src.ways_to_contact[i]);
		}
	}

	return * this;
}

/*
person::person(const char * first, const char * last)
{
	first_name = new char[strlen(first) + 1];
	strcpy(first_name, first);
	
	last_name = new char[strlen(last) + 1];
	strcpy(last_name, last);

	for (int i = 0; i < SIZE; ++i)
	{
		ways_to_contact[i] = NULL;
	}
}
*/

//Add contact infos for a particular person.
int person::add_contact_info(const char * info)
{
	if (!info)
	{
		return 0;	
	}

	for (int i = 0; i < SIZE; ++i)
	{
		if (!ways_to_contact[i])
		{
			ways_to_contact[i] = new char[strlen(info) + 1];
			strcpy(ways_to_contact[i], info);
			return 1;
		}
	}

	//The contact info list for the person is full.
	return -1;
}

//Compare two people.
int person::compare(const person & to_compare) const
{	
	char one = to_compare.first_name[0];
	char two = first_name[0];	

	if (one == two)
	{
		for (int i = 0; i < 100; ++i)
		{
			if (to_compare.first_name[i] > first_name[i])
			{
				return 1;
			}
			else if (to_compare.first_name[i] < first_name[i])
			{
				return -1;
			}
		}
	}

	if (one > two)
	{
		return 1;	
	}	
	else
	{
		return -1;
	}
	
}

//Compare the last name.
int person::compare_last(const char * to_compare) const
{
	return strcmp(last_name, to_compare);
}

//Compare the first name.
int person::compare_first(const char * to_compare) const
{
	return strcmp(first_name, to_compare);
}

//Copy the contacts to another person.
int person::copy_contacts(char **& contacts) const
{
	for (int i = 0; i < SIZE; ++i)
	{
		contacts[i] = new char[strlen(ways_to_contact[i]) + 1];
		strcpy(contacts[i], ways_to_contact[i]);
	}

	return 1;
}

//Display the person's personal information.
int person::display() const
{
	if (!first_name || !last_name)
	{
		return 0;
	}

	cout << first_name << " " << last_name << endl;
	
	for (int i = 0; i < SIZE; ++i)
	{
		if (ways_to_contact[i])	
		{
			cout << "Contact Info " << "#" << i+1 << ": " << ways_to_contact[i] << endl;
		}
	}

	return 1;	
}

//Read the first and last name into the data members.
//Read the 3 contact infos as well.
int person::read(const char * last)
{
	char first_input[100], third_input[100];

	cout << "Enter the person's first name: ";
	cin.get(first_input, 100); cin.ignore(100, '\n');	

	first_name = new char[strlen(first_input) + 1];
	strcpy(first_name, first_input);

	last_name = new char[strlen(last) + 1];
	strcpy(last_name, last);
	
	for (int i = 0; i < SIZE; ++i)
	{
		cout << "Enter the top 3 ways to contact this person: ";
		cin.get(third_input, 100); cin.ignore(100, '\n');
		add_contact_info(third_input);
	}

	return 1;		
}

//Node is a person.
node::node() : person()
{

}

//Copy a person using the base class copy constructor.
node::node(const person & to_copy) : person(to_copy)
{
	
}

//Copy constructor since node is dynamic data.
node & node::operator = (const node & src)
{
	if (this == &src) return * this;

	person::operator=(src);

	next = src.next;
	
	return * this;	
}

//node::node(const char *& first, const char *& last, const char **& ways) : person(first, last, ways)

/*
node::node(const char *& first, const char *& last) : person(first, last)
{

}
*/

//Go to the next node.
node *& node::go_next()
{
	return next;
}

//Link the next node with the previous.
void node::link(node * connection)
{
	next = connection;
}
