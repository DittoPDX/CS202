/*
Steven Tran
CS202 | Program #5
Karla Fant
2/27/2017

This is the java file which handles the place data. The data structure that handles the place data is
a binary search tree. Place is an abstract class, so the user is forced to create only derived Place objects.
The overall program will not allow the user to add any cities or B&Bs. The program's loading of external
files will do that. I should have a minimum of "5" classes within a hierarchy: places, hotel, apartment, 
homestay, city, and citysys. The review uses the LinkedList class.
*/

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.LinkedList;

abstract class Place
{
	protected LinkedList<String> list;
	protected String availability;
	protected String location;
	protected String name;
	protected int price;
	protected int guests;
	
	//Default constructor.
	public Place()
	{
		this.availability = null;
		this.location = null;
		this.name = null;
		this.list = null;
		this.price = 0;
		this.guests = 0;
	}
	
	//Constructor with arguments.
	public Place(String availability, String location, String name, int price, int guests, LinkedList <String> list)
	{
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

	//Basically a copy constructor used for deep copy.
	public Place(Place src)
	{
		//Load a random review from the external file.
		try 
		{
			load();
		} 
		catch (FileNotFoundException e)
		{
			e.printStackTrace();
		}
		
		this.availability = src.availability;
		this.location = src.location;
		this.name = src.name;
		this.price = src.price;
		this.guests = src.guests;
	}
	
	//Compare the names of two B&Bs using the object.
	public int compare(Place to_compare)
	{
		return name.compareTo(to_compare.name);
	}
	
	//Compare the names of two B&Bs.
	public int compare(String to_compare)
	{
		return name.compareTo(to_compare);
	}
	
	//Display the place data for a certain B&B using dynamic binding.
	//Fulfills dynamic binding requirement.
	abstract public int display();
	
	//Displays the linear linked list of reviews.
	public int display_review()
	{
		System.out.println(list);
		return 1;
	}
	
	//Testing out dynamic binding in Java.
	abstract int description();
	
	//Generates random reviews for the B&B places using file io and math.
	public int load() throws FileNotFoundException
	{
		//Create a new linked list of type String.
		list = new LinkedList<String>();
		
		File to_read = new File("Review.txt");
		
		try 
		{
			//This is how the program reads line by line.
			BufferedReader reader = new BufferedReader(new FileReader(to_read));
			
			//Generate a random integer between 0 and 30.
			int rand = (int) (0 + (Math.random() * 30));
			
			//Randomly pick a review.
			for (int i = 0; i <= rand; i++)
			{
				String line = reader.readLine();
				
				if (i == rand)
				{
					list.add(line);
				}
			}
			
			reader.close();
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
	
		return 1;
	}
	
	/*
	 * Both of these mathematical functions show how
	 * Java's function overloading can be applied across
	 * class scopes within a hierarchy.
	 */
	//One function to test class scopes' overloading.
	public int calculate_tip(int payment)
	{
		return (int) (payment  * .15);
	}
	
	//Second function to test class scopes' overloading.
	public int days_to_weeks(int days)
	{
		return days / 7;
	}
	
}