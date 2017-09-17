/*
Steven Tran
CS202 | Program #5
Karla Fant
2/27/2017

This is the java file which handles every city's data. The binary search tree data structure handles the outer tree
which consists of a city. Every city node has an inner tree of places.

I've already implemented the AVL balanced tree in program #3, so I will be implementing a regular BST. This class
implements insert, display, retrieve, retrieve all related items, remove, and remove all. All of these functions are
implemented recursively.
*/

public class CitySys
{
	Node2 root;
	
	//Adds a BNB to the city.
	public int add_bnb(String city_name, Place to_add)
	{
		if (city_name == null) return 0;
		
		return add_bnb(root, city_name, to_add);
	}
	
	//Recursive function for adding a BNB to a city.
	private int add_bnb(Node2 root, String city_name, Place to_add)
	{
		if (root == null) return 0;
		
		//City name matches!
		if (root.compare(city_name) == 0)
		{
			if (to_add instanceof Hotel)
			{
				root.add_place(to_add, 1);
			}
			else if (to_add instanceof Apartment)
			{
				root.add_place(to_add, 2);
			}
			else if (to_add instanceof Homestay)
			{
				root.add_place(to_add, 3);
			}
			return 1;
		}
	
		return add_bnb(root.get_left(), city_name, to_add) +
				       add_bnb(root.get_right(), city_name, to_add);
	}
	
	//Wrapper function to add a city to the outer tree.
	public int add_city(City to_add)
	{
		root = add_city(root, to_add);
		return 1;
	}
	
	//Recursive function to add a city to the outer tree.
	private Node2 add_city(Node2 root, City to_add)
	{
		if (root == null)
		{
			root = new Node2(to_add);
			root.set_left(null); 
			root.set_right(null);
			return root;
		}
		
		//Compares if the name is greater than the existing root.
		int number = root.compare(to_add);
		
		//Adds the data to the tree depending on the name size.
		if (number < 0)
		{
			root.set_right(add_city(root.get_right(), to_add));
		}
		else if (number > 0)
		{
			root.set_left(add_city(root.get_left(), to_add));
		}
		
		//Return the root to make sure it's actually updated.
		return root;
	}
	
	//Wrapper function to display all of the cities.
	public int display_all()
	{
		return display_all(root);
	}
	
	//In-order display of all of the cities.
	private int display_all(Node2 root)
	{
		if (root == null) return 0;
		
		display_all(root.get_left());
		root.display_name();
		root.display_place();
		display_all(root.get_right());
		
		return 1;
	}
	
	//Wrapper function to find BNB place in the city.
	public int find(String to_find, City found)
	{
		if (to_find == null) return 0;
		
		return find(root, to_find, found);
	}
	
	//Recursive function to find a BNB place in the city.
	private int find(Node2 root, String to_find, City found)
	{
		if (root == null) return 0;
		
		if (root.compare(to_find) == 0)
		{
			//Both objects are of type "City".
			found.root = root.root;
			found.name = root.name;
			
			return 1;
		}
		
		return find(root.get_left(), to_find, found) +
		       find(root.get_right(), to_find, found);
	}
	
	//Wrapper function to find a certain BNB place.
	public int find(String to_find, Place found, String search)
	{
		if (to_find == null) return 0;
		
		return find(root, to_find, found, search);
	}
	
	//Recursive function to find a certain BNB place.
	private int find(Node2 root, String to_find, Place found, String search)
	{
		if (root == null) return 0;
		
		//City matches, and now we find the BNB place!
		if (root.compare(search) == 0)
		{
				int check = root.find(to_find, found);
				
				return check;
		}
		
		return find(root.get_left(), to_find, found, search) +
			           find(root.get_right(), to_find, found, search);
	}
	
	//Wrapper function to find a BNB's review.
	public int find_review(String to_find, Place found, String search)
	{
		if (to_find == null) return 0;
		
		return find_review(root, to_find, found, search);
	}
	
	//Recursive function to find a BNB's review.
	private int find_review(Node2 root, String to_find, Place found, String search)
	{
		if (root == null) return 0;
		
		//City matches, and now we find the BNB!
		if (root.compare(search) == 0)
		{
			int check = root.find(to_find, found);
			
			return check;
		}
		
		return find_review(root.get_left(), to_find, found, search) +
			           find_review(root.get_right(), to_find, found, search);
	}
	
	//Wrapper function to find related places in each inner tree.
	public int find_related(String type, Place list[])
	{
		if (type == null || root == null) return 0;
		
		find_related(root, type, list);
		
		return 1;
	}
	
	//Recursive function to find related places in each inner tree.
	private int find_related(Node2 root, String type, Place list[])
	{
		if (root == null) return 0;
		
		root.find_related(type, list);
		
		return find_related(root.get_left(), type, list) +
				       find_related(root.get_right(), type, list);
	}
	
	//Remove wrapper function. (removes a city)
	public int remove(String name)
	{
		if (root == null) return 0;
		
		root = remove(root, name);
		
		return 1;
	}
	
	//Single remove for a binary search tree. (removes a city)
	private Node2 remove(Node2 root, String name)
	{
		if (root == null) return null;
		
		//Go left or right depending on name size.
		if (root.compare(name) > 0)
		{
			root.set_left(remove(root.get_left(), name));
		}
		else if (root.compare(name) < 0)
		{
			root.set_right(remove(root.get_right(), name));
		}
	
		if (root.compare(name) == 0)
		{
			//Left child exists.
			if (root.get_right() == null)
			{
				System.out.println(root.name + " removed!");
				Node2 temp = root.get_left();
				root = null;
				root = temp;
			}
			//Right child exists.
			else if (root.get_left() == null)
			{
				System.out.println(root.name + " removed!");
				Node2 temp = root.get_right();
				root = null;
				root = temp;
			}
			//Both children exist; now find the inorder successor and delete it.
			else if (root.get_left() != null && root.get_right() != null)
			{
				System.out.println(root.name + " removed!");
				Node2 temp = null, curr = root.get_right();
				Node2 prev = null;
				curr  = remove_helper(curr, prev, root, temp);
			}
		}

		return root;
	}
	
	//Helper to remove the in-order successor.
	private Node2 remove_helper(Node2 curr, Node2 prev, Node2 root, Node2 temp)
	{
		if (curr == null) return curr;
		
		if (curr.get_left() == null)
		{
			temp = curr.get_right();
			root.root = curr.root;
			root.name = curr.name;
			curr = null;
			
			if (prev != null)
			{
				prev.set_left(temp);
			}
			else
			{
				root.set_right(temp);
			}
			
			return curr;
		}
		else
		{
			prev = curr;
			return remove_helper(curr.get_left(), prev, root, temp);
		}

	}
	
	//Wrapper function to remove all cities.
	public int remove_all()
	{
		if (root == null) return 0;
		
		root = remove_all(root);
		
		return 1;
	}
	
	//Recursive function to remove all cities.
	private Node2 remove_all(Node2 root)
	{
		if (root == null) return root;
	
		remove_all(root.get_left());
		remove_all(root.get_right());
		root = null;
		
		return root;
	}
	
	//Wrapper function to remove a single BNB from the city.
	public int remove_BNB(String to_remove, String city_name)
	{
		if (to_remove == null || city_name == null) return 0;
		
		return remove_BNB(root, to_remove, city_name);
	}
	
	//Recursive function to remove a single BNB from the city.
	private int remove_BNB(Node2 root, String to_remove, String city_name)
	{
		if (root == null) return 0;
		
		//City name matches, and now we call the city function to remove the BNB place.
		if (root.compare(city_name) == 0)
		{
			return root.remove(to_remove);
		}
		
		return remove_BNB(root.get_left(), to_remove, city_name) +
				       remove_BNB(root.get_right(), to_remove, city_name);
	}
	
	//Wrapper function for verifying a city.
	public int verify_city(String city_name, City temp)
	{
		if (city_name == null) return 0;
		
		return verify_city(root, city_name, temp);
	}
	
	//Recursive function for verifying a city.
	private int verify_city(Node2 root, String city_name, City temp)
	{
		if (root == null) return 0;
		
		//City was found in the list!
		if (root.compare(city_name) == 0)
		{
			temp.root = root.root;
			return 1;
		}
		
		return verify_city(root.get_left(), city_name, temp) +
				       verify_city(root.get_right(), city_name, temp);
	}
}
