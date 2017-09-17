/*
Steven Tran
CS202 | Program #5
Karla Fant
2/27/2017

This is the java file which handles the doubly linked list of arrays. The node class has
next and previous pointers. This node class "is a" city because it needs to manipulate
city data. Each node has an array and an index to be updated.
*/

//This class is the doubly-linked list.
public class Node3 extends City
{
	protected Node3 next;
	protected Node3 prev;
	protected Place array[];
	protected int index;
	
	//Every node3 should have a city name.
	public Node3()
	{
		this.next = null;
		this.prev = null;
		this.array = null;
		this.index = 0;
	}
	
	//Calls the base class constructor to set the data.
	public Node3(City src)
	{
		super(src);
	}
	
	//Set the next pointer.
	public void set_next(Node3 next)
	{
		this.next = next;
	}
	
	//Set the previous pointer.
	public void set_prev(Node3 prev)
	{
		this.prev = prev;
	}
	
	//Get the next pointer.
	public Node3 get_next()
	{
		return this.next;
	}
	
	//Get the previous pointer.
	public Node3 get_prev()
	{
		return this.prev;
	}
}