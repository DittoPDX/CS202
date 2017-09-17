/*
Steven Tran
CS202 | Program #5
Karla Fant
2/27/2017

This is the java file which handles the Homestay data. Homestay is a type of a BNB place.
Like apartment and hotel, homestay manipulates its unique data.
*/

import java.util.LinkedList;

//Home-stay is a type of B&B where the user can rent out a room in a home.
public class Homestay extends Place
{
	
	//Default constructor.
	public Homestay()
	{
		
	}
	
	//Constructor to manually load everything in.
	public Homestay(String availability, String location, String name, int price, int guests, LinkedList <String> list)
	{
		super(availability, location, name, price, guests, list);
	}
	
	//Copy constructor.
	public Homestay(Homestay to_add) 
	{
		super(to_add);
	}
	
	//Copies the place object into the homestay.
	public Homestay(Place to_add) 
	{
		super(to_add);
	}

	@Override
	//Testing out dynamic binding (not very useful).
	int description() 
	{
		System.out.println("You can get the home-environment while traveling!");
		return 0;
	}
	
	@Override
	//Testing out useful dynamic binding function.
	public int display()
	{
		System.out.println(this.getClass().getName());
		System.out.println("BNB Name: " + name);
		System.out.println("Price: $" + price);
		System.out.println("Guests: " + guests);
		System.out.println("Location: " + location);
		System.out.println("Availability: " + availability);
		System.out.println();
		
		return 1;
	}
	
	//First function to test class scopes' overloading.
	public float calculate_tip(float payment)
	{
		return (float) (payment * .15);
	}
	
	//Second function to test class scopes' overloading.
	public double days_to_weeks(double days)
	{
		return days / 7;
	}

}