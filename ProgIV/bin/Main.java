/*
Steven Tran
CS202 | Program #4
Karla Fant
2/27/2017

This is the main file which uses the user interface class. The application uses the hierarchy (CitySys).
*/

import java.util.Scanner;

public class Main 
{
	public static void main(String [] args)
	{	
		CitySys sys = new CitySys();
		Scanner scan = new Scanner(System.in);
		String response = new String();
		
		//Preload the data from an external file.
		//For simplicity's sake, I am only using five cities.
		City Portland = new City("Portland");
		Portland.load();
		City Seattle = new City("Seattle");
		Seattle.load();
		City SanDiego = new City("San Diego");
		SanDiego.load();
		City Nevada = new City("Nevada");
		Nevada.load();
		City Arizona = new City("Arizona");
		Arizona.load();

		sys.add_city(Portland);
		sys.add_city(Seattle);
		sys.add_city(SanDiego);
		sys.add_city(Nevada);
		sys.add_city(Arizona);
		
		do
		{
			UserInterface ui = new UserInterface();
			int option = ui.display_menu();
			int result = ui.menu(sys, option);
			
			if (result == 0)
			{
				System.out.println("Keeping Portland Weird!");
				scan.close();
				return;
			}
			
			System.out.println("Continue (y/n)? ");
			response = scan.nextLine();
			
		} while (response.equals("y"));
		
		scan.close();
		System.out.println("Keeping Portland Weird!");
		return;
		
	}
}
