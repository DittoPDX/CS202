/*
Steven Tran
CS202 | Program #5
Karla Fant
2/27/2017

This is the java file which handles the user interface. I figured it'd be easier for the grader to just power
through the application to test every functions available. #10 uses dynamic binding. #8 and 9 uses the
function overloading across class scopes (simple mathematical functions). The rest of the options
test the inner and outer binary search trees.

Options 11-17 are program #5 options.
*/

import java.util.Scanner;

public class UserInterface 
{
	protected Scanner input = new Scanner(System.in);
	
	public int display_menu()
	{
		System.out.println("~Book Me B&B App~\t\t\t\t\t ~Personalize Your Trip~");
		System.out.println("0. Exit the application\t\t\t\t\t11. Add a city&place to your travel list!");
		System.out.println("1. Display all cities & their B&BS\t\t12. Find a BNB place in your list's cities!");
		System.out.println("2. Find a city and display all B&Bs\t\t13. Find all related BNB places in your list");
		System.out.println("3. Find related places for B&B type\t14. Remove a BNB place from your travel list!");
		System.out.println("4. Remove all cities & B&Bs\t\t\t15. Remove a single city from your list!");
		System.out.println("5. Remove a city & its B&Bs\t\t\t16. Remove all cities from your list!");
		System.out.println("6. Remove a city's B&B\t\t\t\t17. Display your entire list!");
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

	public int menu(CitySys sys, Person person, int option) 
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
			case 11:
			{
				System.out.println("~Add a Place to Your BNB Trip~");
				String repeat;
				do
				{
					System.out.print("Enter an existing city: ");
					String city_name = input.nextLine();
					City temp = new City(city_name);
				
					if (sys.verify_city(city_name, temp) == 1)
					{
						System.out.print("Enter an existing BNB for that city: ");
						String BNB_name = input.nextLine();
					
						//Helps reduce the amount of user input.
						//System.out.println("1) Hotel... 2) Apartment... 3) Homestay? ");
						//int opt = input.nextInt();
						int opt = temp.verify_nametype(BNB_name);
					
						if (opt == 1)
						{
							Place found = new Hotel();
							if (sys.find(BNB_name, found, city_name) == 1)
							{
								System.out.println("BNB Added!");
								person.add_city(temp, found, 1);
							}
							else
							{
								System.out.println("Failure to add BNB");
							}
						}
						if (opt == 2)
						{
							Place found = new Apartment();
							if (sys.find(BNB_name, found, city_name) == 1)
							{
								System.out.println("BNB Added!");
								person.add_city(temp, found, 2);
							}
							else
							{
								System.out.println("Failure to add BNB");
							}
						}
						if (opt == 3)
						{
							Place found = new Homestay();
							if (sys.find(BNB_name, found, city_name) == 1)
							{
								System.out.println("BNB Added!");
								person.add_city(temp, found, 3);
							}
							else
							{
								System.out.println("Failure to add BNB");
							}
						}
					}
					else
					{
						System.out.println("City not found :(");
					}
				
					System.out.println("Again (y/n)? ");
					repeat = input.nextLine();
				
			    } while (repeat.equals("y"));
				
				break;
			}
			case 12: //Find a BNB in the current user travel list.
			{
				System.out.println("~Find BNB Place in List of Cities~");
				System.out.print("Enter a BNB: ");
				String bnb_place = input.nextLine();
				Place found[] = new Place[1];
				
				//System.out.print("Enter an existing city: ");
				//String city_name = input.nextLine();
				//City temp = new City(city_name);

				//sys.find(bnb_place, found, city_name);
				int check = person.find_BNB(bnb_place, found);
				if (check == 0)
				{
					System.out.println("Uh oh... BNB not found! :(");
					return 1;
				}
				
				found[0].display();
				break;
			}
			case 13: //Find all related places in the user list.
			{
				System.out.println("~Find Related BNBS in List~");
				System.out.print("Enter (Hotel, Apartment, Homestay): ");
				String response = input.nextLine();
				
				if (response.equals("Hotel") || response.equals("Apartment") || response.equals("Homestay"))
				{
					Place list[] = new Place[100];
					person.find_related(response, list);
				
					for (int i = 0; i < 100; ++i)
					{
						if (list[i] != null)
						{
							list[i].display();
						}
					}
					
					list = null;
					
				}
				else
				{
					System.out.println("Invalid response :(");
				}
				
				break;
			}
			case 14: //Remove BNB place from user list.
			{
				System.out.println("~Removing A BNB From City~");
				System.out.println("Removes the most recent BNB in the city");
				//System.out.print("Enter a BNB: ");
				System.out.print("Enter a city: ");
				String bnb_place = input.nextLine();
				
				//System.out.print("Enter a city: ");
				//String city_name = input.nextLine();
				
				int success = person.remove_BNB(bnb_place);
				
				if (success == 1)
				{
					System.out.println("BNB removed!");
				}
				else
				{
					System.out.println("No BNB to remove :(");
				}
				break;
			}
			case 15: //Remove a single city from the user list.
			{
				System.out.println("~Removing A City~");
				System.out.print("Enter a city: ");
				String response = input.nextLine();
				
				int success = person.remove(response);
				if (success == 1)
				{
					System.out.println(response + " removed!");
				}
				else
				{
					System.out.println("No city to remove :(");
				}
				break;
			}
			case 16: //Remove all cities from user list.
			{
				System.out.println("~Removing All Cities~");
				System.out.print("Are you sure (y/n)? ");
				
				String response = input.next();
				
				if (response.equals("y"))
				{
					person.remove_all();
				}
				
				break;
			}
			case 17:
			{
				person.display_cities();
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
