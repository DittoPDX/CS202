/*
Steven Tran
CS202 | Program #4
Karla Fant
2/27/2017

This is the java file which handles the outer tree's node (Node2). The node class has left and
right pointers. This node class inherits from city to establish the outer tree.
*/

public class Node2 extends City
{
	protected Node2 left;
	protected Node2 right;
	
	//Every node2 should have a city name.
	public Node2()
	{
		this.left = null;
		this.right = null;
	}
	
	//Calls the base class constructor to set the data.
	public Node2(City src)
	{
		super(src);
	}
	
	//Set the left pointer.
	public void set_left(Node2 left)
	{
		this.left = left;
	}
	
	//Set the right pointer.
	public void set_right(Node2 right)
	{
		this.right = right;
	}
	
	//Get the left pointer.
	public Node2 get_left()
	{
		return this.left;
	}
	
	//Get the right pointer.
	public Node2 get_right()
	{
		return this.right;
	}
}