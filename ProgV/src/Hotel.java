/*
Steven Tran
CS202 | Program #5
Karla Fant
2/27/2017

This is the java file which handles the Hotel data. Hotel is a type of a BNB place.
Like apartment and homestay, hotel manipulates its unique data.
*/

import java.io.FileNotFoundException;
import java.util.LinkedList;

//Hotels are a type of B&B where the user has many rooming options.
public class Hotel extends Place
{
	
	//Default constructor.
	public Hotel()
	{
		super();
	}
	
	//Constructor for loading everything manually.
	public Hotel(String availability, String location, String name, int price, int guests, LinkedList <String> list)
	{
		super(availability, location, name, price, guests, list);
		
		//Load a random review from the external file.
		try 
		{
			load();
		} 
		catch (FileNotFoundException e) 
		{
			e.printStackTrace();
		}
		
		this.availability = availability;
		this.location = location;
		this.name = name;
		this.price = price;
		this.guests = guests;
		this.list = list;
	}

	//Copy constructor.
	public Hotel(Hotel to_add) 
	{
		super(to_add);
	}

	//Copy constructor.
	public Hotel(Place to_add) 
	{
		super(to_add);
	}

	@Override
	//Testing out dynamic binding (not very useful).
	int description() 
	{
		System.out.println("You have 30+ rooming options at a hotel!");
		return 0;
	}
	
	@Override
	//Useful operator overloading.
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