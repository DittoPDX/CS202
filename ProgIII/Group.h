/*
Steven Tran
CS202 | Program #3
Karla Fant
2/12/2017

This is the header file class that contains the prototypes for the group class
which manages all of the people in it with the same last name organized by first name 
using the linear linked list data structure. A group "has" a node which "is a" person.
*/

#ifndef GROUP
#define GROUP
#include "Node.h"

class group
{
	public:
		group();
		group(const group & src);
		~group();

		int add_person(const person & to_add);
		int compare(const char * to_compare) const;
		int compare(const group & to_compare) const;
		int compare(const person & to_compare) const;
		int display() const;
		int display_name() const;
		int find(const char * to_find, char *& if_found, char **& contacts) const;
		int read();
		int read(char * group_name);
		int remove(const char * to_remove);
		int remove_all();

		//These operators help move people into a group.
		group & operator = (const group & src);
		group operator + (const person & to_add);
		group & operator += (const person & to_add);

		//These relational operators help compare numbers of people in different groups.
		bool operator < (const group & to_compare);
		bool operator > (const group & to_compare);
		bool operator <= (const group & to_compare);
		bool operator >= (const group & to_compare);

		//These operators help do some group name checks.
		bool operator != (const group & to_compare);
		bool operator == (const group & to_compare);
		bool operator ! ();

		friend istream & operator >> (istream & is, group & to_add);
		friend ostream & operator << (ostream & os, const group & to_display);

	protected:
		char * name;
		node * head;

		int clear_all(node *& head);
		int copy_people(node *& dest, node * src);
		int add_person(node *& head, const person & to_add);
		int count_people(node * head) const;
		int display(node * head) const;
		int find(node * head, const char * to_find, char *& if_found, char **& contacts) const;
		int remove(node *& head, const char * to_remove);
};
#endif
