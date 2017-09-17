/*
Steven Tran
CS202 | Program #2
Karla Fant
2/02/2017

This is the header file for the rider history part of the program. The function prototypes below are
the ones that will allow the actual user to add, remove, display, etc. The data structure
behind this header file is a linear linked list where each node2 has an array of M riding experiences.
*/

#ifndef TRANSIT_RIDER
#define TRANSIT_RIDER
#include <cctype>
#include <cstring>
#include <iostream>

using namespace std;

const int SIZE = 5;

namespace ride_collection
{
	class rider
	{
		public:
			rider();
			rider(const rider & src);
			~rider();

			int add(const char * to_add);
			int remove();
			int remove_all();
			int retrieve(char *& to_retrieve);
			void display() const;
			void display_recent() const;
		
		protected:
			class node2 * head;
			int top_index;

			void copy_LLL(node2 *& dest, node2 * src);
			void clear_all(node2 *& head);
			void display(node2 * head) const;
			int remove_all(node2 *& head);
			int retrieve(node2 * head, char *& to_retrieve);

		
	};

	class history
	{
		public:
			history(const char **& to_copy);
			history(const history & to_copy);
			history();
			~history();
		
			//Experience manipulation functions.	
			void display() const;
			void display_recent() const;
			void add(const char *& to_add);
			void remove();
			int retrieve_info(char *& to_compare) const;
	
		protected:
			char ** ride_history;
			int index;
	};

	class node2 : public history
	{
		public:
			node2(const char **& ride_history);
			node2(const history & to_copy);
			node2();
		
			node2 *& go_next();
			void link(node2 * connection);
	
		protected:
			node2 * next;
	};
}
#endif
