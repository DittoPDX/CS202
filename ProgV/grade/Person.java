/*
Steven Tran
CS202 | Program #5
Karla Fant
2/27/2017

This is the java file which handles the user data. Person extends the city system so that it could read
all of the city data. By allowing person to read the city data, person can update the doubly linked list
of arrays where the arrays represent the BNB places in that city. Each "DLL" node "has an" array of
places (4 total indices).

Note to the grader: the assignment pdf did not indicate that all of the algorithms for a DLL needed
to be implemented with only recursion (only mention was with the binary search trees). 
This class manages the add, single delete, delete all, find one BNB, find all related BNBs, and display.
*/

public class Person extends CitySys
{
	protected Node3 head;
	
	public Person()
	{
		head = null;
	}
	//Wrapper function to add a city to the list.
	public int add_city(City to_add, Place place, int option)
	{
		return add_city_helper(to_add, place, option);
	}
	
	//Recursive function to add a city to the doubly linked list.
	private int add_city_helper(City to_add, Place place, int option)
	{
		Node3 temp = head;
		
		//Create a node if head doesn't exist.
		if (head == null)
		{
			head = new Node3(to_add);
			head.array = new Place[5];
			
			if (option == 1)
			{
				head.array[head.index] = new Hotel(place);
			}
			else if (option == 2)
			{
				head.array[head.index] = new Apartment(place);
			}
			else if (option == 3)
			{
				head.array[head.index] = new Homestay(place);
			}
			
			head.set_next(null);
			head.set_prev(null);
			++head.index;
			return 1;
		}
		
		//If index reaches maximum, then make a new node.
		//If the city name doesn't match, then create a new node for it.
		if (head.index == 4 || head.compare(to_add) != 0)
		{
			head.index = 0;
			temp = head;
			head = new Node3(to_add);
			head.array = new Place[5];
			
			if (option == 1)
			{
				head.array[head.index] = new Hotel(place);
			}
			else if (option == 2)
			{
				head.array[head.index] = new Apartment(place);
			}
			else if (option == 3)
			{
				head.array[head.index] = new Homestay(place);
			}
			
			head.set_next(temp);
			temp.set_prev(head);
			++head.index;
		}
		else //Continue adding at the end like a stack.
		{
			if (option == 1)
			{
				head.array[head.index] = new Hotel(place);
			}
			else if (option == 2)
			{
				head.array[head.index] = new Apartment(place);
			}
			else if (option == 3)
			{
				head.array[head.index] = new Homestay(place);
			}
			
			++head.index;
		}
		
		return 1;
	}
	
	//Wrapper function to display all of the cities and their arrays of BNBs.
	public int display_cities()
	{
		if (head == null) return 0;
		
		return display_cities(head);
	}
	
	//Recursive function to display all of the cities and their arrays of BNBs.
	private int display_cities(Node3 head)
	{
		if (head == null) return 0;
	
		head.display_name();
		
		//Iterature through all of the places.
		for (int i = 4; i >= 0; --i)
		{
			//As long as the array isn't null.
			if (head.array[i] != null)
			{
				head.array[i].display();
			}
		}
		
		return display_cities(head.get_next());
	}
	
	//Wrapper function to find a BNB in the city.
	public int find_BNB(String to_find, Place found[])
	{
		if (head == null) return 0;
		
		return find_BNB(head, to_find, found, 0);
	}
	
	//Recursive function to find a BNB in the city.
	private int find_BNB(Node3 head, String to_find, Place found[], int temp)
	{
		if (head == null) return 0;
		
		//Go through the indices.
		for (int i = 4; i >= 0; --i)
		{
			//Make sure to not dereference null.
			if (head.array[i] != null)
			{
					 //Found the BNB, and now return it to the user.
					if (head.array[i].compare(to_find) == 0)
					{
						if (head.array[i].getClass().getName().equals("Apartment"))
						{
							//Make sure to copy the data back to the client.
							found[temp] = head.array[i];
						}
						else if (head.array[i].getClass().getName().equals("Hotel"))
						{
							found[temp] = head.array[i];	
						}
						else if (head.array[i].getClass().getName().equals("Homestay"))
						{
							found[temp] = head.array[i];
						}
						return 1;
					}
			}
		}
		
		return find_BNB(head.get_next(), to_find, found, temp);
	}
	
	//Wrapper function to find all of the related BNBS.
	public int find_related(String type, Place list[])
	{
		if (type == null) return 0;
		
		return find_related(head, type, list, 0);
	}
	
	//Private function to find all of the related BNBs.
	private int find_related(Node3 head, String type, Place list[], int temp)
	{
		if (head == null) return 0;
		
		for (int i = 0; i < 100 && head.array[i] != null; ++i)
		{	
			//Add every related place to what will be returned back to client.
			if (head.array[i].getClass().getName().equals(type))
			{
				if (list[temp] == null)
				{
						if (type.equals("Hotel"))
						{
							list[temp] = new Hotel(head.array[i]);
						}
						else if (type.equals("Apartment"))
						{
							list[temp] = new Apartment(head.array[i]);
						}
						else if (type.equals("Homestay"))
						{
							list[temp] = new Homestay(head.array[i]);
						}
						
						++temp;
					}
				}
			}
		
		return find_related(head.get_next(), type, list, temp);
	}
	
	//Wrapper function to remove a single city.
	//If there are multiple cities of the same name, then
	//the most recent city created will be destroyed.
	public int remove(String to_find)
	{
		if (head == null) return 0;
		
		Node3 alias = head;
		return remove(alias, to_find);
	}
	
	//Recursive function to remove a single city.
	private int remove(Node3 alias, String to_find)
	{
		if (alias == null) return 0;

		//Alias is now pointing to the matching city.
		if (alias.compare(to_find) == 0)
		{
			//Remove the front node
			if (alias.get_prev() == null)
			{
				head = alias.get_next();
				
				if (head == null)
				{
					return 1;
				}
				
				if (head.get_prev() != null)
				{
					head.set_prev(null);
				}
				
				return 1;
			}
			//Remove the end node.
			else if (alias.get_next() == null)
			{
				Node3 tmp = alias.get_prev();
				
				if (head.get_next() != null)
				{
					tmp.set_next(null);
				}
				
				return 1;
			}
            else //Remove the middle node
            {
                    alias.get_prev().set_next(alias.get_next());
                    alias.get_next().set_prev(alias.get_prev());
                    
                    return 1;
            }
		}
		
		return remove(alias.get_next(), to_find);
	}
	
	//Wrapper function to remove all of the cities.
	public int remove_all()
	{
		if (head == null) return 0;
		
		head = remove_all(head);
		return 1;
	}
	
	//Recursive function to remove all of the cities.
	private Node3 remove_all(Node3 head)
	{
		if (head == null) return null;
		
		//Clear all of the data by going to the end and recursing back.
		remove_all(head.get_next());
		head = null;
		
		return head;
	}
	
	//Wrapper function to remove a single BNB index in a city.
	public int remove_BNB(String city_name)
	{
		if (city_name == null) return 0;
		
	   return remove_BNB(head, city_name);
	}
	
	//Recursive function to remove a single BNB index in a city.
	private int remove_BNB(Node3 head, String city_name)
	{
		if (head == null) return 0;
		
		if (head.name.equals(city_name))
		{
			//Iterate through the array.
			for (int i = 4; i >= 0; --i)
			{
				if (head.array[i] != null)
				{
					//Clear memory at that index. No need to decrement as it nullifies the index.
					head.array[i] = null;
					return 1;
				}
			}
		}
		return remove_BNB(head.get_next(), city_name);
	}
}
