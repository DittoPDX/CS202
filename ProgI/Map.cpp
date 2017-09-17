/*
Steven Tran
CS202 | Program #1 | Portland Streetcar Interactive Map
Karla Fant
01/25/2017

This is the graph adjacency list implementation file. All of the traversals are implemented
recursively. The user can display the A-Loop, NS-Line, and connecting stops on each
particular line. For a CLL, it should only be one way which is forward. For a DLL, it
should be two ways which is forward unless the stop is an end stop.
*/

#include "Map.h"

using namespace std;

//Return head by reference.
node *& vertex::get_head()
{
	return head;
}

//Add a stop to the vertex array slot.
void vertex::add_stop(const char * to_add)
{
	stop temp(to_add);
	stop_name = temp;
}

//Get stop by reference.
stop & vertex::get_stop()
{
	return stop_name;
}

//Compare stop data for find location function in graph.
int vertex::compare(const stop & to_compare)
{
	return stop_name.compare(to_compare);
}

//Get adjacent by reference.
vertex *& node::get_adjacent()
{
	return adjacent;
}

//Go next to follow OOP principles.
node *& node::go_next()
{
	return next;
}

//Link one pointer to another.
void node::link(node * connection)
{
	next = connection;
}

//Link one node to an adjacent slot on a vertex slot.
void node::linkad(vertex * connection)
{
	adjacent = connection;
}

//Constructor to set up the size of the map.
graph::graph(int size)
{
	adjacency_list = new vertex[size];
	helper(0, size);	
	list_size = size;	
}

//Helper function to avoid loops inside constructor.
void graph::helper(int temp, int size)
{
	if (temp < size)
	{
		adjacency_list[temp].get_head() = NULL;	
		helper(++temp, size);
	}
}

//Destructor to clear all vertices.
graph::~graph()
{
	clear_all_helper(0);
	
	if (adjacency_list)
	{
		delete [] adjacency_list;
		adjacency_list = NULL;
	}
}

//Helper function to replace loop inside destructor.
void graph::clear_all_helper(int temp)
{
	if (temp < list_size)
	{
		clear_all(adjacency_list[temp].get_head());
		clear_all_helper(temp + 1);
	}
}

//Helper recursive function to clear all head pointers in graph.
void graph::clear_all(node *& head)
{
	if (!head)
	{
		return;
	}

	clear_all(head -> go_next());

	if (head)
	{
		delete head;
		head = NULL;
	}
}

//Inserts a vertex with stop data.
int graph::insert_vertex(char * to_add)
{
	return insert_vertex_helper(to_add, 0);
}

//Helper function that replaces a loop for inserting a vertex.
int graph::insert_vertex_helper(char * to_add, int temp)
{
	if (temp < list_size)
	{
		if (!adjacency_list[temp].get_stop())
		{
			adjacency_list[temp].add_stop(to_add);
			return 1;
		}
		
		if (temp == (list_size - 1) && !(!adjacency_list[temp].get_stop()))
		{
			return -1;
		}

		insert_vertex_helper(to_add, temp + 1);
	}

	return 1;
}

//Inserting an edge which is connecting two vertices with a node.
int graph::insert_edge(stop & current_vertex, stop & to_attach)
{
	int conn_one = find_location(current_vertex);
	int conn_two = find_location(to_attach);

	if (conn_one == -1 || conn_two == -1)
	{
		return -1;
	}

	//Create a new node, link adjacent, and link head.
	node * temp = new node;
	temp -> linkad(&adjacency_list[conn_two]);
	temp -> link(adjacency_list[conn_one].get_head());
	adjacency_list[conn_one].get_head() = temp;

	return 1;
}

//Finds location of a particular vertex.
int graph::find_location(const stop & key_value)
{
	return find_location_helper(key_value, 0);
}

//Helper function for replacing the loop part of finding a vertex.
int graph::find_location_helper(const stop & key_value, int temp)
{
	if (temp < list_size)
	{	
		if (!adjacency_list[temp].get_stop())
		{
			return -1;
		}
		
		if (!adjacency_list[temp].compare(key_value))
		{
			return temp;
		}
		
	}

	return find_location_helper(key_value, temp + 1);
	
}

int graph::display_all()
{
	int success = display_all(0);

	return success;
}

int graph::display_all(int temp)
{
	if (temp < list_size)
	{
		if (!adjacency_list[temp].get_stop())
		{
			return -1;
		}
		else if (temp == 0 && (!adjacency_list[temp].get_stop()))
		{
			return -1;
		}

		adjacency_list[temp].get_stop().display();
		display_all(temp + 1);
	}

	return -1;
}

//Displays the A-Loop in my program.
int graph::display_loop()
{
	int success = display_loop(0);

	return success;
}

//Helper function to avoid loops.
int graph::display_loop(int temp)
{
	if (temp < 12)
	{
		if (!adjacency_list[temp].get_stop())
		{
			return -1;
		}
		else if (temp == 0 && (!adjacency_list[temp].get_stop()))
		{
			return -1;
		}

		adjacency_list[temp].get_stop().display();
		display_loop(temp + 1);
	}

	return -1;
}

//Displays the NS-Line in my program.
int graph::display_line()
{
	int success = display_line(12);
	return success;
}

//Helper function to avoid loops.
int graph::display_line(int temp)
{
	if (temp < 23)
	{
		if (!adjacency_list[temp].get_stop())
		{
			return -1;
		}	
		else if (temp == 0 && (!adjacency_list[temp].get_stop()))
		{
			return -1;	
		}

		adjacency_list[temp].get_stop().display();
		display_line(temp + 1);
	}

	return -1;
}

//This is the code that allows displaying connected vertices.
int graph::display_adjacent(const stop & key_value)
{
	int index = find_location(key_value);

	if (index == -1)
	{
		return -1;
	}

	return display_adjacent(adjacency_list[index].get_head());
}

//The recursive call for displaying connected vertices.
int graph::display_adjacent(node * head)
{
	if (!head)
	{
		return 0;
	}

	head -> get_adjacent() -> get_stop().display();

	return display_adjacent(head -> go_next());
}

//Connects the first 12 stops of the A-Loop.
int graph::connect_loop_stops()
{
	int success = connect_loop_stops_helper(0);	
	return success;
}

//Helper function to connect first 12 stops and replaces loop with recursion.
int graph::connect_loop_stops_helper(int temp)
{
	if (temp < list_size)
	{
		if (temp == 11)
		{
			insert_edge(adjacency_list[temp].get_stop(), adjacency_list[0].get_stop());
		}
		if (!adjacency_list[temp + 1].get_stop())
		{
			return -1;
		}
			
		insert_edge(adjacency_list[temp].get_stop(), adjacency_list[temp+1].get_stop());
		connect_loop_stops_helper(temp + 1);
	}

	return -1;

}

//Connects the stops between 12-23 for NS-Line.
int graph::connect_loop_stops2()
{
	int success = connect_loop_stops_helper2(12);
	return success;
}

//Helper function to connect the back-n-forth stops with recursion.
int graph::connect_loop_stops_helper2(int temp)
{
	if (temp < list_size)
	{
		if (!adjacency_list[temp + 1].get_stop())
		{
			return -1;
		}

		//Undirected graph for DLL.
		insert_edge(adjacency_list[temp].get_stop(), adjacency_list[temp+1].get_stop());
		insert_edge(adjacency_list[temp+1].get_stop(), adjacency_list[temp].get_stop());
		connect_loop_stops_helper2(temp+1);	
	}

	return -1;
}

//Function loads an external file in.
int graph::load(const char file[])
{
	//File is not found.
	if (!file)
	{
		return 0;
	}	
	
	//Variables to manage data storage.
	ifstream file_in;

	//Local variables to manage reading in from file.
	char stop_data[100];

	//Open the file and then read util the file reaches EOF.
	file_in.open(file);

	if (file_in.is_open())
	{
		while (!file_in.eof())
		{
			//Stopping condition.
			if (file_in.peek() == -1)
			{
				return 1;
			}

			//Read from .txt file.
			file_in.get(stop_data, 100, ':'); file_in.ignore(100, '\n');
		
			//Insert a vertex.
			insert_vertex(stop_data);	
		}
	}

	return 1;

} 
