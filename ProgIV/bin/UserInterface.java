/*
Steven Tran
CS202 | Program #4
Karla Fant
2/27/2017

This is the java file which handles the user interface. I figured it'd be easier for the grader to just power
through the application to test every functions available. #10 uses dynamic binding. #8 and 9 uses the
function overloading across class scopes (simple mathematical functions). The rest of the options
test the inner and outer binary search trees.
*/

import java.util.Scanner;

public class UserInterface 
{
	protected Scanner input = new Scanner(System.in);
	
	public int display_menu()
	{
		System.out.println("~Book Me B&B App~");
		System.out.println("0. Exit the application");
		System.out.println("1. Display all cities & their B&BS");
		System.out.println("2. Find a city and display all B&Bs: ");
		System.out.println("3. Find related places for B&B type");
		System.out.println("4. Remove all cities & B&Bs");
		System.out.println("5. Remove a city & its B&Bs");
		System.out.println("6. Remove a city's B&B");
		System.out.println("7. Find a B&B in the city");
		System.out.println("8. Tip Calculator: ");
		System.out.println("9. Days Calculator for B&B Place");
		System.out.println("10. Check previous tenant reviews");
		
		int option = 0;
		System.out.print("Enter an option: ");
		option = input.nextInt();
		System.out.println();
		input.nextLine();
		
		return option;
	}

	public int menu(CitySys sys, int option) 
	{
		switch(option)
		{
			case 0:
			{	
				return 0;
			}
			case 1:
			{
				sys.display_all();	
				
				break;
			}
			case 2:
			{
				System.out.println("~Find a city to display~");
				System.out.print("Enter a city name: ");
				
				String name = input.nextLine();
				City temp = new City();
				System.out.println();
				sys.find(name, temp);
				temp.display_place();
				
				break;
			}
			case 3:
			{
				System.out.println("~Find All Places for Specific B&B Type~");
				System.out.print("Enter (Hotel, Apartment, Homestay): ");
				String response = input.nextLine();
				
				if (response.equals("Hotel") || response.equals("Apartment") || response.equals("Homestay"))
				{
					Place list[] = new Place[100];
					sys.find_related(response, list);
				
					for (int i = 0; i < 100; ++i)
					{
						if (list[i] == null)
						{
							return 1;
						}
						list[i].display();
					
					}
				}
				else
				{
					System.out.println("Invalid response :(");
				}
				break;
			}
			case 4:
			{
				System.out.println("~Removing All Cities~");
				System.out.print("Are you sure (y/n)? ");
				
				String response = input.next();
				if (response.equals("y"))
				{
					sys.remove_all();
				}
				
				break;
			}
			case 5:
			{
				System.out.println("~Removing One City~");
				System.out.print("Enter a city name: ");
				
				String response = input.nextLine();
				sys.remove(response);
				
				break;
			}
			case 6:
			{
				System.out.println("~Remove a City's B&B");
				
				System.out.print("Enter a city: " );
				String city_name = input.nextLine();
				
				System.out.print("Enter the B&B name: ");
				String bnb_name = input.nextLine();
				
				sys.remove_BNB(bnb_name, city_name);
				break;
			}
			case 7:
			{
				System.out.println("~Find B&B in the System~");
				
				System.out.print("Enter a B&B name: ");
				String response = input.nextLine();
				
				System.out.print("Enter a city: ");
				String response2 = input.nextLine();
			
				City to_find = new City(response2);
				int verify = sys.verify_city(response2, to_find);
				if (verify != 1)
				{
					System.out.println("City not found :(");
					return 1;
				}
				int opt = to_find.verify_nametype(response);
				
				if (opt == 1)
				{
					Place temp = new Hotel();
					int success = sys.find(response, temp, response2);
					if (success == 1)
					{
						temp.display();
					}
				}
				else if (opt == 2)
				{
					Place temp = new Apartment();
					int success = sys.find(response, temp, response2);
					if (success == 1)
					{
						temp.display();
					}
				}
				else if (opt == 3)
				{
					Place temp = new Homestay();
					int success = sys.find(response, temp, response2);
					if (success == 1)
					{
						temp.display();
					}
					
				}
				
				break;
			}
			case 8:
			{
				System.out.println("~TIP Calculator for B&B Place~");
				
				System.out.println("Enter in your payment: ");
			    int payment = input.nextInt();
			    
			    System.out.println("Payment option 1 or 2: ");
			    int opt = input.nextInt();
			    
			    System.out.println("1) Hotel ... 2) Apartment ... 3) Homestay : ");
			    int type = input.nextInt();
			    
			    if (opt == 1)
			    {
			    	if (type == 1)
			    	{
						Hotel temp = new Hotel();
						System.out.println(temp.calculate_tip(payment));
			    	}
			    	if (type == 2)
			    	{
						Apartment temp = new Apartment();
						System.out.println(temp.calculate_tip(payment));
			    	}
			    	if (type == 3)
			    	{
						Homestay temp = new Homestay();
						System.out.println(temp.calculate_tip(payment));
			    	}
			    }
			    
			    if (opt == 2)
			    {
			    	float pay = (float) payment;
			    	if (type == 1)
			    	{
						Hotel temp = new Hotel();
						System.out.println(temp.calculate_tip(pay));
			    	}
			    	if (type == 2)
			    	{
						Apartment temp = new Apartment();
						System.out.println(temp.calculate_tip(pay));
			    	}
			    	if (type == 3)
			    	{
						Homestay temp = new Homestay();
						System.out.println(temp.calculate_tip(pay));
			    	}
			    }
				break;
			}
			case 9:
			{
				System.out.println("~Days Calculator for B&B Place~");
				
				System.out.println("Enter in your # of days : ");
			    int days = input.nextInt();
			    
			    System.out.println("Days option 1 or 2: ");
			    int opt = input.nextInt();
			    
			    System.out.println("1) Hotel ... 2) Apartment ... 3) Homestay : ");
			    int type = input.nextInt();
			    
			    if (opt == 1)
			    {
			    	if (type == 1)
			    	{
						Hotel temp = new Hotel();
						System.out.println(temp.days_to_weeks(days));
			    	}
			    	if (type == 2)
			    	{
						Apartment temp = new Apartment();
						System.out.println(temp.days_to_weeks(days));
			    	}
			    	if (type == 3)
			    	{
						Homestay temp = new Homestay();
						System.out.println(temp.days_to_weeks(days));
			    	}
			    }
			    
			    if (opt == 2)
			    {
			    	float other_days = (float) days;
			    	if (type == 1)
			    	{
						Hotel temp = new Hotel();
						System.out.println(temp.days_to_weeks(other_days));
			    	}
			    	if (type == 2)
			    	{
						Apartment temp = new Apartment();
						System.out.println(temp.days_to_weeks(other_days));
			    	}
			    	if (type == 3)
			    	{
						Homestay temp = new Homestay();
						System.out.println(temp.days_to_weeks(other_days));
			    	}
			    }
				
				break;
			}
			case 10:
			{
				System.out.println("~Find B&B in the System~");
				
				System.out.print("Enter a B&B name: ");
				String response = input.nextLine();
				
				System.out.print("Enter a city: ");
				String response2 = input.nextLine();

				City to_find = new City(response2);
				int verify = sys.verify_city(response2, to_find);
				if (verify != 1)
				{
					System.out.println("City not found :(");
					return 1;
				}
				int opt = to_find.verify_nametype(response);

				if (opt == 1)
				{
					Place temp = new Hotel();
					int success = sys.find_review(response, temp, response2);
					
					if (success == 1)
					{
						temp.display_review();
					}
					
				}
				if (opt == 2)
				{
					Place temp = new Apartment();
					int success = sys.find_review(response, temp, response2);
					if (success == 1)
					{
						temp.display_review();
					}
				}
				if (opt == 3)
				{
					Place temp = new Homestay();
					int success = sys.find_review(response, temp, response2);
					if (success == 1)
					{
						temp.display_review();
					}
					
				}
				
				break;
			}
			default:
			{
				break;
			}
		}
		
		return 1;
	}
}
