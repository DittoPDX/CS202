/*
Steven Tran
CS202 | Program #1 | Portland Streetcar Interactive Map
Karla Fant
01/25/2017

This is the implementation file for the Type.h header. The main objective of this .cpp
file is implement the logic behind the pacing between streetcars managed by each
type of line, a loop or a back-n-forth line.

The rule for the back-n-forth line is that two trains may be able to be at one spot at a time after changing directions.
*/

#include "Type.h"

int loop::load(const char file[])
{
	if (!file)
	{
		return 0;
	}

	//Initializes and opens a file.
	ifstream file_in;
	file_in.open(file);

	//This is where input will be read.
	char stop_name[MAX];

	//Opens file.
	if (file_in.is_open())
	{
		while (!file_in.eof())
		{
			//Checks earlier than condition in while loop.
			//This conditional allows us to ignore the blank line.	
			if (file_in.peek() == -1)
			{
				return 1;
			}
			
			//Read every line from text file
			file_in.get(stop_name, MAX, ':'); file_in.ignore(MAX, '\n');
	
			//Add the stop to the line.
			add_stop(stop_name);
		}
	}	

	return 1; 
}

//Default constructor is created.
loop::loop()
{

}

//Call base class constructor to set line name.
loop::loop(char * name): line(name)
{

}

loop::~loop()
{
	if (head)
	{
		cnode * temp = head -> go_next();
		head -> link(NULL);
		clear_all(temp);
	}
}

//Recursive helper function to delete all nodes in a CLL.
void loop::clear_all(cnode *& head)
{
	if (!head)
	{
		return;
	}

	clear_all(head -> go_next());
	delete head;
	head = NULL;
}

//Add a stop to the loop list.
int loop::add_stop(char * stop_name)
{
	if (!stop_name)
	{
		return 0;
	}	

	if (!head)
	{
		head = new cnode(stop_name);
		head -> link(head);
		return 1;
	}

	cnode * temp = new cnode(stop_name);
	temp -> link(head -> go_next());
	head -> link(temp);
	head = temp;

	return 1;
}

//Display all of the stops on the loop.
int loop::display_stops() const
{
	if (!head)
	{
		return 0;
	}

	cnode * start = head -> go_next();
	head -> go_next() = NULL;

	int stops = display_stops(start);
	head -> link(start);

	return stops;
}

//Helper recursive function to display those stops.
int loop::display_stops(cnode * head) const
{
	if (!head)
	{
		return 0;
	}	

	head -> display();

	display_stops(head -> go_next());
	return 1;
}

//Verify car location to make sure the streetcar exists on a track.
int loop::verify_car_location(char * location) const
{
	if (!head || !location)
	{
		return 0;	
	}

	cnode * start = head -> go_next();
	head -> link(NULL);

	int verify = verify_car_location(start, location);
	head -> link(start);
	return verify;
}

//Helper function to make sure it exists on the loaded track.
int loop::verify_car_location(cnode * head, char * location) const
{
	if (!head)
	{
		return 0;
	}

	if (head -> compare(location) == 0)
	{
		return 1;	
	}

	return verify_car_location(head -> go_next(), location);
}

/*
Runs the streetcar on the A-Loop.
The algorithm behind this is that each line has an array containing four streetcars.
The algorithm iterates through every car with the rest to check the distances.
*/
int loop::run_streetcar(char * car_name)
{
	if (!car_name)
	{
		return 0;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (line_streetcars[i].compare(car_name) == 0)
		{
			int distance = check_pacing(line_streetcars[i]);

			if (distance == -5)
			{
				cnode * start = head -> go_next();
				int compare = compare_location(start, line_streetcars[i]);
				return compare;
			}
			else if (distance == -2)
			{
				return -3;
			}
			else
			{
				cnode * start = head -> go_next();
				int compare = compare_location(start, line_streetcars[i]);
				return compare;
			}
		}
	}

	return 0;
}

//This is the helper function for the run streetcar which
//should update the current location to the next available stop.
int loop::compare_location(cnode * head, streetcar & to_update) const
{
	if (!head)
	{
		return 0;
	}

	int check = to_update.compare_location(head -> get_stop());
	
	if (check == 0)
	{
		to_update.update_location(head -> go_next() -> get_stop());
		return 1;
	}

	return compare_location(head -> go_next(), to_update);
}

//This is the algorithm that compares a streetcar with the rest for the
//entire array of streetcars that a line has.
int loop::check_pacing(streetcar & pace_check)
{
	if (!pace_check)
	{
		return -1;
	}
	
	for (int i = 0; i < 4; ++i)
	{
		
		if (!line_streetcars[i])
		{
			return 0;
		}
	
		if (!line_streetcars[1])
		{
			return -5;
		}

		if (pace_check != line_streetcars[i])
		{
			cnode * car_one = head, * car_two = head;	
			car_one = obtain_location(car_one, pace_check);
			car_two = obtain_location(car_two, line_streetcars[i]);

			int distance = calculate_pace_distance(head, car_one -> get_stop(), car_two -> get_stop());
			int check = pace_check.get_pace_difference(distance);

			if (check == -2)
			{
				return -2;
			}	
		}
	}

	return -1;
}

//This obtains a location of the current streetcar.
cnode * loop::obtain_location(cnode * head, streetcar & pace_check)
{
	if (!head)
	{
		return NULL;
	}

	if (pace_check.compare_location(head -> get_stop()) == 0)
	{
		return head;
	}
	
	return obtain_location(head -> go_next(), pace_check);
}

//This calculates the distance of two streetcars.
int loop::calculate_pace_distance(cnode * head, char * location_one, char * location_two)
{
	if (!head)
	{
		return 0;
	}
	
	if (head -> compare(location_one) == 0)
	{
		return cpd(head, location_two);
	}
	
	return calculate_pace_distance(head -> go_next(), location_one, location_two);
}

//This is the recursive helper function that counts the distance between
//the first car and the second car.
int loop::cpd(cnode * head, char * location_two)
{
	if (head -> compare(location_two) == 0)
	{
		return 0;
	}

	return cpd(head -> go_next(), location_two) + 1;
}

/*
					End of CLL logic management.
------------------------------------------------------------------------------------------------
*/

int nsline::load(const char file[])
{
	if (!file)
	{
		return 0;
	}

	//Initialize file and load file.
	ifstream file_in;
	file_in.open(file);

	//This is the input storage.
	char stop_name[MAX];

	//Open the file.
	if (file_in.is_open())
	{
		while (!file_in.eof())
		{
			//Checks earlier than condition in while loop.
			//This conditional allows us to ignore the blank line.	
			if (file_in.peek() == -1)
			{
				return 1;
			}
			
			//Read every line from text file
			file_in.get(stop_name, MAX, ':'); file_in.ignore(MAX, '\n');

			//Load the stop.
			add_stop(stop_name);
		}
	}	

	return 1; 
}

//Created the default constructor.
nsline::nsline()
{

}

//Call the parent constructor to initialize the line name.
nsline::nsline(char * name) : line(name)
{

}

nsline::~nsline()
{
	if (head2)
	{
		clear_all(head2);
	}
}

//Recursive function to delete all of the DLL nodes.
void nsline::clear_all(dnode *& head2)
{
	if (!head2)
	{
		return;
	}

	clear_all(head2 -> go_next());

	delete head2;
	head2 = NULL;
}

//Add a stop to the NS-Line.
int nsline::add_stop(char * stop_name)
{
	if (!stop_name)
	{
		return 0;
	}

	if (!head2)
	{
		head2 = new dnode(stop_name);
		head2 -> link_next(NULL);
		head2 -> link_prev(NULL);
		return 1;
	}
		
	return add_stop(head2, stop_name);
}

//Recursive helper function to add a stop after the first stop.
int nsline::add_stop(dnode *& head2, char * stop_name)
{
	if (!head2)
	{
		return 0;
	}

	dnode * front = head2 -> go_next();

	if (!head2 -> go_next())
	{
		front = new dnode(stop_name);
		front -> link_next(NULL);
		front -> link_prev(head2);
		head2 -> link_next(front);
		return 1;
	}

	return add_stop(head2 -> go_next(), stop_name);
}

//Display all of the stops for a DLL/NS-Line.
int nsline::display_stops() const
{
	if (!head2)
	{
		return 0;
	}

	return display_stops(head2);
}

//Recursive helper function to display all the stops for the NS-Line.
int nsline::display_stops(dnode * head2) const
{
	if (!head2)
	{
		return 0;
	}	

	head2 -> display();
	display_stops(head2 -> go_next());

	return 1;
}

//Verifies if the streetcar is on an existing location.
int nsline::verify_car_location(char * location) const
{
	if (!head2 || !location)
	{
		return 0;
	}

	int verify = verify_car_location(head2, location);
	return verify;
}

//Recursive helper function to check for the streetcar location.
int nsline::verify_car_location(dnode * head2, char * location) const
{
	if (!head2)
	{
		return 0;
	}

	if (head2 -> compare(location) == 0)
	{
		return 1;
	}

	return verify_car_location(head2 -> go_next(), location);
}

/*
This is the run streetcar for a back-n-forth track.
The algorithm is to simply go through all of the 4 streetcars and
compare each one to the rest. Then the pace is calculated, and then the streetcar
moves based upon the calculated pace.
*/
int nsline::run_streetcar(char * car_name)
{
	if (!car_name)
	{
		return 0;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (line_streetcars[i].compare(car_name) == 0 && line_streetcars[i].check_flag() == -1000)
		{
			int distance = check_pacing(line_streetcars[i]);
		
			if (distance == 0)
			{
				int compare = compare_location(head2, line_streetcars[i]);
				return compare;
			}
			else if (distance == -2)
			{
				return 0;
			}
			else
			{
				int compare = compare_location(head2, line_streetcars[i]);
				return compare;
			}
		}
		else if (line_streetcars[i].compare(car_name) == 0 && line_streetcars[i].check_flag() == 1000)
		{
			int distance = check_pacing(line_streetcars[i]);
			
			if (distance == 0)
			{
				int compare = compare_location2(head2, line_streetcars[i]);
				return compare;
			}
			else if (distance == -2)
			{
				return 0;	
			}
			else
			{
				int compare = compare_location2(head2, line_streetcars[i]);
				return compare;
			}
		}
	}

	return 0;
}

//This is the operation to move the streetcar by one stop.
int nsline::compare_location(dnode * head2, streetcar & to_update) const
{
	if (!head2)
	{
		return 0;
	}

	int check = to_update.compare_location(head2 -> get_stop());
	
	if (check == 0 && !head2 -> go_next())
	{
		//Every streetcar has a flag for direction.
		to_update.reverse_flag();
		to_update.update_location(head2 -> go_prev() -> get_stop());
		return 1;
	}
	
	if (check == 0)
	{
		to_update.update_location(head2 -> go_next() -> get_stop());
		return 1;
	}

	return compare_location(head2 -> go_next(), to_update);
}

//This is the operation to move the streetcar by one stop backwards.
int nsline::compare_location2(dnode * head2, streetcar & to_update) const
{
	if (!head2)
	{
		return 0;
	}

	int check = to_update.compare_location(head2 -> get_stop());

	if (check == 0 && !head2 -> go_prev())
	{
		//Every streetcar has a flag for direction.
		to_update.reverse_flag();
		to_update.update_location(head2 -> go_next() -> get_stop());
		return 1;
	}

	if (check == 0)
	{
		to_update.update_location(head2 -> go_prev() -> get_stop());
		return 1;
	}

	return compare_location2(head2 -> go_next(), to_update);
}

//This function checks the pacing between two cars.
//If the pacing is more than whatever pacing a car has between another car,
//then the car should move by one stop.
int nsline::check_pacing(streetcar & pace_check)
{
	if (pace_check.check_flag() == -1000)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (!line_streetcars[0])
			{
				return 0;
			}

			if (!line_streetcars[i])
			{
				return -5;
			}

			int distance = 0, check = 0;

			if (pace_check != line_streetcars[i] && (pace_check.compare_flags(line_streetcars[i]) == 1000))
			{
				dnode * car_one = head2, * car_two = head2;
				car_one = obtain_location(car_one, pace_check);
				car_two = obtain_location(car_two, line_streetcars[i]);
				distance = calculate_pace_distance(head2, car_one -> get_stop(), car_two -> get_stop());

				if (distance < 0)
				{
					distance = 0;
				}

				check = pace_check.get_pace_difference(distance);
			}

			if (check == -2)
			{
				return -2;
			}
		}	
	}
	else if (pace_check.check_flag() == 1000)
	{
		for (int i = 0; i < 4; ++i)
		{
			if (!line_streetcars[0])
			{
				return 0;
			}

			if (!line_streetcars[i])
			{
				return -5;
			}

			int distance = 0, check = 0;

			if (pace_check != line_streetcars[i] && (pace_check.compare_flags(line_streetcars[i]) == 1000))
			{
				dnode * car_one = head2, * car_two = head2;
				car_one = obtain_location(car_one, pace_check);
				car_two = obtain_location(car_two, line_streetcars[i]);			
				distance = calculate_pace_distance2(head2, car_one -> get_stop(), car_two -> get_stop());

				if (distance < 0)
				{
					distance = 0;
				}

				check = pace_check.get_pace_difference(distance);
			}

			if (check == -2)
			{
				return -2;
			}
		}
	}

	return 0;
}

//Obtains location of one streetcar.
dnode * nsline::obtain_location(dnode * head2, streetcar & pace_check)
{
	if (!head2)
	{
		return 0;
	}

	if (pace_check.compare_location(head2 -> get_stop()) == 0)
	{
		return head2;
	}

	return obtain_location(head2 -> go_next(), pace_check);
}

//Calculates pace difference by passing the two cars into a helper function.
int nsline::calculate_pace_distance(dnode * head2, char * location_one, char * location_two)
{
	if (!head2)
	{
		return -111;
	}

	if (head2 -> compare(location_one) == 0)
	{
		return cpd(head2, location_two);
	}
	
	return calculate_pace_distance(head2 -> go_next(), location_one, location_two);
}

//Calculates pace difference by passing the two cars into the helper function.
//This function is for backwards movement.
int nsline::calculate_pace_distance2(dnode * head2, char * location_one, char * location_two)
{
	if (!head2)
	{
		return -111;
	}

	if (head2 -> compare(location_one) == 0)
	{
		return cpd2(head2, location_two);
	}	
	
	return calculate_pace_distance2(head2 -> go_next(), location_one, location_two);
}

//This is the helper function for calculating the difference between two cars.
int nsline::cpd(dnode * head2, char * location_two)
{
	if (!head2)
	{
		return -111;
	}

	if (head2 -> compare(location_two) == 0)
	{
		return 0;
	}

	return cpd(head2 -> go_next(), location_two) + 1;
}

//This is the helper function for calculating the difference between two cars
//for backwards movement.
int nsline::cpd2(dnode * head2, char * location_two)
{
	if (!head2)
	{
		return -111;
	}

	if (head2 -> compare(location_two) == 0)
	{
		return 0;
	}

	return cpd2(head2 -> go_prev(), location_two) + 1;
}
