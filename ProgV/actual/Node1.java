/*
Steven Tran
CS202 | Program #5
Karla Fant
2/27/2017

This is the java file which handles the inner tree's node (Node1) and the outer tree's node (Node2).
Both node classes have left and right pointers. The first node class "has a" Place while the second
node class "is a" city.
*/

public class Node1
{
	protected Node1 left;
	protected Node1 right;
	protected Place place;
	
	//Default constructor for the first node.
	public Node1(int option)
	{
		this.left = null;
		this.right = null;
		
		if (option == 1)
		{
			this.place = new Hotel();
		}
		else if (option == 2)
		{
			this.place = new Apartment();
		}
		else if (option == 3)
		{
			this.place = new Homestay();
		}
	}
	
	//Sets the left pointer.
	public void set_left(Node1 left)
	{
		this.left = left;
	}
	
	//Sets the right pointer.
	public void set_right(Node1 right)
	{
		this.right = right;
	}
	
	//Gets the left pointer.
	public Node1 get_left()
	{
		return this.left;
	}
	
	//Gets the right pointer.
	public Node1 get_right()
	{
		return this.right;
	}
	
}