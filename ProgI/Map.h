/*
Steven Tran
CS202 | Program #1 | Portland Streetcar Interactive Map
Karla Fant
01/25/2017

This is the graph with adjacency list implementation. As stated in the assignments, only node classes can have getters and setters only (vertex and node). In my implementation,
the graph adjacency list is providing user options such as displaying and searching for connecting stops. Overall, it shows how the lines, stops, and directions work.
*/

#include <fstream>
#include <cstdlib>
#include <iostream>
#include "Node.h"

class vertex
{
	public:
		//Getters and setters to manage head and stops.
		class node *& get_head();
		void add_stop(const char * to_add);
		stop & get_stop();

		//Compare stops for the find location function.
		int compare(const stop & to_compare);

	protected:
		stop stop_name;
		class node * head;
};

class node
{
	public:
		vertex *& get_adjacent();
		node *& go_next();

		void link(node * connection);
		void linkad(vertex * connection);

	protected:
		vertex * adjacent;
		node * next;
};

class graph
{
	public:
		//My map has 22 stops total. The requirement is 20.
		graph(int size = 23);
		~graph();

		//Connects the stops for the CLL and DLL tracks.
		int connect_loop_stops();
		int connect_loop_stops2();

		//Display functions for different lines and all lines.	
		int display_all();
		int display_adjacent(const stop & key_value);
		int display_loop();
		int display_line();

		//Graph adjacency list implementation.
		int find_location(const stop & key_value);
		int insert_vertex(char * to_add);
		int insert_edge(stop & current_vertex, stop & to_attach);

		int load(const char file[]);

	protected:
		
		//These are the helper functions which are purely recursive functions.
		void helper(int temp, int size);
		void clear_all(node *& head);
		void clear_all_helper(int temp);
	
		//Display functions.
		int display_adjacent(node * head);
		int display_all(int temp);
		int display_loop(int temp);
		int display_line(int temp);

		//Graph implementation helpers.
		int find_location_helper(const stop & key_value, int temp);
		int insert_vertex_helper(char * to_add, int temp);

		//Recursive function helpers for connecting the stops together to form lines.
		int connect_loop_stops_helper(int temp);	
		int connect_loop_stops_helper2(int temp);
	
		vertex * adjacency_list;
		int list_size;		
};
