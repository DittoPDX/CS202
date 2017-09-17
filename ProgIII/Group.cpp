/*
Steven Tran
CS202 | Program #3
Karla Fant
2/12/2017

This is the .cpp file which contains the implementations for the group class 
which manages all of the people with the same last name. However, the group class'
core functionaltiy is to sort all of the names alphabetically.
*/

#include "Group.h"

//Constructor with initialization list.
group::group() : name(NULL), head(NULL)
{

}

//Copy constructor for group class.
group::group(const group & src)
{
	name = new char[strlen(src.name) + 1];
	strcpy(name, src.name);
		
	if (src.head)
	{
		copy_people(head, src.head);
	}
}

//Destructor for group class.
group::~group()
{
	if (name)
	{
		delete [] name;
	}

	if (head)
	{
		clear_all(head);
	}
}

//Recursive clear function.
int group::clear_all(node *& head)
{
	if (!head)
	{
		return 0;
	}

	clear_all(head -> go_next());

	delete head;
	head = NULL;
	return 1;
}

//Wrapper function for adding a person.
int group::add_person(const person & to_add)
{
	if (to_add.compare_last(name) != 0)
	{
		return 0;
	}

	return add_person(head, to_add);	
}

//Recursive add that keeps the list sorted.
int group::add_person(node *& head, const person & to_add)
{
	if (!head)
	{
		head = new node(to_add);
		head -> link(NULL);
		return 1;
	}
	
	if (head -> compare(to_add) == -1)
	{
		node * temp = head;
		head = new node(to_add);
		head -> link(temp);
		return 1;
	}
	
	if (head -> compare(to_add) == 1)
	{
		return add_person(head -> go_next(), to_add);
	}

	return 1;
}

//Wrapper function for displaying.
int group::display() const
{
	if (!head)
	{
		return 0;
	}

	return display(head);
}

//Recursive function for displaying.
int group::display(node * head) const
{
	if (!head)
	{
		return 0;
	}

	head -> display();

	return display(head -> go_next()) + 1;
}

//Regular function for displaying group name.
int group::display_name() const
{
	if (!name)
	{
		return 0;
	}

	cout << name;

	return 1;
}

//Main read function used to get data from the user.
int group::read()
{
	char input[100];
	cout << "Enter the group last name (e.g. Smith): ";
	cin.get(input, 100); cin.ignore(100, '\n');

	name = new char[strlen(input) + 1];
	strcpy(name, input);

	cout << "The group name is: " << name << endl;

	char response;

	do
	{
		person p;
		p.read(name);
		add_person(p);
		
		cout << "Add another person (y/n)? ";
		cin.get(response); cin.ignore();

	} while (response == 'y');

	return 1;
}

//Another read function for the group but not used in application.
int group::read(char * group_name)
{
	name = new char[strlen(group_name) + 1];
	strcpy(name, group_name);
	
	cout << "The group name is: " << name << endl;
	return 1;
}

//Wrapper function for removing a person.
int group::remove(const char * to_remove)
{
	if (!to_remove) return 0;

	return remove(head, to_remove);
}

//Recursive remove function for removing a single person.
int group::remove(node *& head, const char * to_remove)
{
	if (!head) return 0;

	if (!head -> go_next() && head -> compare_first(to_remove) == 0)
	{
		delete head;
		head = NULL;		
		return 1;
	}

	if (head -> compare_first(to_remove) == 0)
	{
		node * temp = head -> go_next();
		delete head;
		head = temp;
		return 1;
	}

	return remove(head -> go_next(), to_remove);	
}

//Removes all of the people inside the group.
int group::remove_all()
{
	if (!head) return 0;

	clear_all(head);

	return 1;
}

//Compares group name.
int group::compare(const char * to_compare) const
{
	return strcmp(name, to_compare);
}

//Compares group name using group object.
int group::compare(const group & to_compare) const
{
	return strcmp(name, to_compare.name);
}

/*
int group::compare(const person & to_compare) const
{
	return 1;	
}
*/

//Finds the person and his/her contact information.
int group::find(const char * to_find, char *& if_found, char **& contacts) const
{
	if (!to_find)
	{
		return 0;
	}

	return find(head, to_find, if_found, contacts);
}

//Recursive function for finding the person plus the contact information.
int group::find(node * head, const char * to_find, char *& if_found, char **& contacts) const
{
	if (!head)
	{
		return 0;
	}

	if (head -> compare_first(to_find) == 0)
	{
		if_found = new char[strlen(to_find) + 1];
		strcpy(if_found, to_find);
		head -> copy_contacts(contacts);

		return 1;
	}

	return find(head -> go_next(), to_find, if_found, contacts);
}

//Assignment operator copy the data into one object to another.
group & group::operator = (const group & src)
{
	if (this == &src)
	{
		return *this;
	}

	if (name)
	{
		delete [] name;
	}	

	name = new char[strlen(src.name) + 1];
	strcpy(name, src.name);

	if (head)
	{
		clear_all(head);
	}	
	
	copy_people(head, src.head);

	return * this;
}

//Appends a person to a copy of a group object.
group group::operator + (const person & to_add)
{
	group temp = *this;
	temp.add_person(to_add);
	return group(temp);
}

//Appends a person to the referred group object.
group & group::operator += (const person & to_add)
{
	add_person(to_add);
	return * this;
}

//Determines if one group is smaller than the other.
bool group::operator < (const group & to_compare)
{
	if (!head) return true;
	if (!to_compare.head) return false;

	if (count_people(head) < to_compare.count_people(to_compare.head))
	{
		return true;
	}

	return false;
}

//Determines if one group is bigger than the other.
bool group::operator > (const group & to_compare)
{
	if (!head) return false;
	if (!to_compare.head) return true;

	if (count_people(head) > to_compare.count_people(to_compare.head))
	{
		return true;	
	}

	return false;
}

//Determines if one group is smaller than or equal to the other.
bool group::operator <= (const group & to_compare)
{
	if (!head && !to_compare.head) return true;
	if (!head) return true;
	if (!to_compare.head) return false;

	if (count_people(head) <= to_compare.count_people(to_compare.head))
	{
		return true;
	}

	return false;
}

//Determines if one group is bigger than or equal to the other.
bool group::operator >= (const group & to_compare)
{
	if (!head && !to_compare.head) return true;
	if (!head) return false;
	if (!to_compare.head) return true;

	if (count_people(head) >= to_compare.count_people(to_compare.head))
	{
		return true;
	}

	return false;
}

//Determines if group exists or not.
bool group::operator ! ()
{
	return (!name);
}

//Checks if two names are not equal.
bool group::operator != (const group & to_compare)
{
	if (compare(to_compare) != 0)
	{
		return true;
	}

	return false;
}

//Checks if two names are equal.
bool group::operator == (const group & to_compare)
{
	if (compare(to_compare) == 0)
	{
		return true;
	}

	return false;
}

//Reads in a group name and the list of people to add.
istream & operator >> (istream & is, group & to_add)
{
	to_add.read();
	return is;	
}

//Displays the list of people.
ostream & operator << (ostream & os, group & to_display)
{
	to_display.display();
	return os;
}

//Copy people function used in copy constructor.
int group::copy_people(node *& dest, node * src)
{
	if (!src)
	{
		dest = NULL;
		return 0;
	}
	
	dest = new node(*src);

	return copy_people(dest -> go_next(), src -> go_next());
}

//Used with the relational operators.
int group::count_people(node * head) const
{
	if (!head) return 0;

	return count_people(head -> go_next()) + 1;
}
