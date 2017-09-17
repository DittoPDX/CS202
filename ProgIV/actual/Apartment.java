/*
Steven Tran
CS202 | Program #4
Karla Fant
2/27/2017

This is the java file which handles the apartment data. Apartment is a type of a BNB place.
Like hotel and homestay, apartment manipulates its unique data.
*/

import java.util.LinkedList;

//Apartments are a type of B&B where the user gets more privacy.
public class Apartment extends Place
{
	
	//Default constructor.
	public Apartment()
	{
		super();
	}
	
	//Constructor to load data in manually.
	public Apartment(String availability, String location, String name, int price, int guests, LinkedList <String> list)
	{
		super(availability, location, name, price, guests, list);
	}
	
	//Copy constructor.
	public Apartment(Apartment to_add) 
	{
		super(to_add);
	}
	
	//Copy the place object into the apartment.
	public Apartment(Place to_add) 
	{
		super(to_add);
	}

	@Override
	//Testing out dynamic binding (not very useful).
	int description() 
	{
		System.out.println("You get a lot of privacy in only one room choice!");
		return 0;
	}
	
	@Override
	//Testing out dynamic binding (quite useful).
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