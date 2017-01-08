#include "clist.h"
#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

//Consider:
//Do you need helper functions?
//Is head or tail recursion better?
//Remove the block comments form the function below to get started
//The question is: Write a function to display the list. Return the number of nodes.
//The difficulty of this question is: 0

int dA(node * head)
{
	if (!head)
	{
		return 0;
	}
		
	cout << head -> data << " ";

	return dA(head -> next) + 1;
}

int displayAll(node * head)
{
	if (!head)
	{
		return 0;
	}
	
	node * start = head -> next;	
	head -> next = NULL;

	int items = dA(start);

	head -> next = start;

	return items;
}

//Place the prototype in the appropriate .h file
//Consider:
//Do you need helper functions?
//Is head or tail recursion better?
//Remove the block comments form the function below to get started
//The question is: Write a function to display the list in reverse order. Return the number of nodes.
//The difficulty of this question is: 0

int dR(node * head)
{
	if (!head)
	{
		return 0;
	}	

	//Call function and then display	
	//Recursive call here gets to the last node then returns back
	int items = dR(head -> next) + 1;
	cout << head -> data << " ";

	return items;
}

int displayReverse(node* head)
{
	if (!head)
	{
		return 0;
	}

	node * start = head -> next;
	head -> next = NULL;

	int items = dR(start);
	start -> next = head;

	return items;	
}

//Place the prototype in the appropriate .h file
//Consider:
//Do you need helper functions?
//Is head or tail recursion better?
//Remove the block comments form the function below to get started
//The question is: Write a function to display every node that is divisible by the argument passed in. Return number of nodes displayed.
//The difficulty of this question is: 0

int dD(node * head, int toDisplay)
{
	if (!head)
	{
		return 0;
	}

	if (head -> data % toDisplay == 0)
	{
		cout << head -> data << " ";
	}

	return dD(head -> next, toDisplay) + 1;
}

int displayDivisible(node * head, int toDisplay)
{
	if (!head)
	{
		return 0;
	}

	node * start = head -> next;
	head -> next = NULL;

	int items = dD(start, toDisplay);
	head -> next = start;
	
	return items;
}


//Place the prototype in the appropriate .h file
//Consider:
//Do you need helper functions?
//Is head or tail recursion better?
//Remove the block comments form the function below to get started
//The question is: Write a function to display every other Node in the list. Return the number of nodes that are not displayed.
//The difficulty of this question is: 1

int dEO(node * head)
{
	if (!head)
	{
		return 0;
	}

	if (!head -> next)
	{
		cout << head -> data;
		return 1;
	}	

	cout << head -> data << " ";
	
	int items = dEO(head -> next -> next) + 1;

	return items;
}

int displayEveryOther(node * head)
{
	if (!head)
	{
		return 0;
	}

	node * first = head -> next;
	node * start = head -> next -> next;
	head -> next = NULL;

	int items = dEO(start);
	head -> next = first;	

	return items;
}


//Place the prototype in the appropriate .h file
//Consider:
//Do you need helper functions?
//Is head or tail recursion better?
//Remove the block comments form the function below to get started
//The question is: Write a function to add the sum of the data from the first two nodes to the end of the list. Return the sum of the list. 
//The difficulty of this question is: 1


int addToEnd(node *& head)
{
	if (!head)
	{
		return 0;
	}

	node * start = head -> next;
	node * first = head -> next;
	node * second = head -> next -> next;
	head -> next = NULL;

	int listSum = returnSum(start);
	int sum_data = first -> data + second -> data;

	//Create new node, set data, set head pointing to last node,
	//move head to be last node, have head point to front	
	node * temp = new node;
	temp -> data = sum_data;
	head -> next = temp;
	head = temp;
	temp -> next = first;

	return listSum;	
}

int returnSum(node * head)
{
	if (!head)
	{	
		return 0;
	}

	return returnSum(head -> next) + head -> data;
}


//Place the prototype in the appropriate .h file
//Consider:
//Do you need helper functions?
//Is head or tail recursion better?
//Remove the block comments form the function below to get started
//The question is: Write a function to add the data passed in to the function after every instance of a 2 in the list. Return the number of nodes that were added to the list.
//The difficulty of this question is: 1


int addAfter2(node *& head, int toAdd)
{
	if (!head)	
	{
		return 0;
	}
	
	node * start = head -> next;
	head -> next = NULL;	

	int nodes = ADDAF2(start, toAdd);
	head -> next = start;

	return nodes;	
}

int ADDAF2(node *& head, int toAdd)
{
	if (!head)
	{
		return 0;
	}

	node * front = head -> next;

	if (head -> data == 2)
	{
		node * temp = new node;
		temp -> data = toAdd;
		head -> next = temp;
		temp -> next = front;	
		return ADDAF2(head -> next, toAdd) + 1;
	}
	else
	{
		ADDAF2(head -> next, toAdd);
	}
}

//Place the prototype in the appropriate .h file
//Consider:
//Do you need helper functions?
//Is head or tail recursion better?
//Remove the block comments form the function below to get started
//The question is: Write a function to add the data passed in to the function before every instance of a 2 in the list. Return the number of nodes that were added to the list.
//The difficulty of this question is: 1


int addBefore2(node *& head, int toAdd)
{
	if (!head)
	{
		return 0;			
	}	

	node * start = head -> next;
	head -> next = NULL;

	int nodes = ADDBF2(start, toAdd);
	head -> next = start;

	return nodes;	
}

int ADDBF2(node *& head, int toAdd)
{
	if (!head)
	{
		return 0;
	}

	if (head -> data == 2)
	{
		node * temp = head;	
		head = new node;
		head -> data = toAdd;
		head -> next = temp;

		//Recursive call with temp instead of head
		//to hang onto existing list
		return 1 + ADDBF2(temp -> next, toAdd);
	}

	ADDBF2(head -> next, toAdd);
}

//Place the prototype in the appropriate .h file
//Consider:
//Do you need helper functions?
//Is head or tail recursion better?
//Remove the block comments form the function below to get started
//The question is: Write a function to add the data of the first node that is divisible by three or five to every following node in the list. Return number of nodes that occur before one is divisible by three or five.
//The difficulty of this question is: 3

/*
Algorithm:
Add first node data to right of every node that is divisible by 3 or 5.
1. Get the first node data
2. Check if node is divisible by 3 or 5
3. Add if true else continue going through LLL

Wrapper function:
1. Convert CLL to LLL
2. Reconnect after appending all of the nodes
*/
int modifyAfter(node *& head)
{
	if (!head)
	{
		return 0;
	}

	node * first = head -> next;
	node * start = head -> next -> next;
	head -> next = NULL;

	int nodes = mA(start, first -> data);
	head -> next = first;

	return nodes;
}

int mA(node *& head, int fData)
{
	if (!head)
	{
		return 0;
	}

	node * front = head -> next;

	if (head -> data % 3 == 0 || head -> data % 5 == 0)
	{
		node * temp = new node;
		temp -> data = fData;
		head -> next = temp;
		temp -> next = front;	
		return mA(head -> next, fData) + 1;
	} 
	else
	{
		mA(head -> next, fData);
	}

	
}


//Place the prototype in the appropriate .h file
//Consider:
//Do you need helper functions?
//Is head or tail recursion better?
//Remove the block comments form the function below to get started
//The question is: Write a function to reverse the List. Return number of nodes in the list.
//The difficulty of this question is: 3

/*
Algorithm:
1. Wrapper function
2. Reverse function that returns a new reversed list
3. Small function that returns number of nodes reversed and
allows reconnection to become CLL
*/
int reverseAll(node *& head)
{
	if (!head)
	{
		return 0;
	}
	
	node * start = head -> next;
	head -> next = NULL;

	start = rA(start);
	node * current = head;

	int nodes = rA2(head);	
	head -> next = current;

	return nodes;	
}

node * rA(node * head)
{
	if (!(head && head -> next))
	{
		return 0;
	}
	else
	{
		node * newhead = rA(head -> next);
		head -> next -> next = head;
		head -> next = NULL;
		return newhead;
	}	

/* 	//Iterative Solution
	node * curr = head;
	node * prev = NULL;
	node * temp;

	while (curr)
	{
		temp = curr -> next;
		curr -> next = prev;
		prev = curr;
		curr = temp;
	}

	head = prev;	
*/

}

int rA2(node *& head)
{
	if (!head -> next)
	{
		return 0;
	}
	else
	{
		head = head -> next;
		return rA2(head) + 1;
	}
}


//Place the prototype in the appropriate .h file
//Consider:
//Do you need helper functions?
//Is head or tail recursion better?
//Remove the block comments form the function below to get started
//The question is: Write a function to add a node that contains the data passed into the function at the end of the list for each node that is divisible by the first node's data
//The difficulty of this question is: 3

/*
Algorithm:
1. Wrapper function
	-Converts CLL to LLL
	-Converts LLL to CLL
2. Adding function
	-Adds passed in data to end of list whenever
	 a node is divisible by the first node's data
*/

int appendIfDivisible(node *& head, int toAdd)
{
	if (!head)
	{
		return 0;
	}

	node * first = head -> next;
	node * start = head -> next;
	head -> next = NULL;

	int numToAdd = checker(start, start -> data);
	int tempCount = numToAdd;
	aID(start, toAdd, tempCount);

/*
	Iterative solution
	for (int i = 0; i < tempCount; ++i)
	{
		node * temp = new node;
		temp -> data = toAdd;
		head -> next = temp;
		head = temp;
		head -> next = first;
	}
*/

	rA2(head);
	head -> next = first;
	return numToAdd;
	
}

int aID(node *& head, int toAdd, int count)
{
	if (!head)
	{
		node * temp = new node;
		temp -> data = 100;
		head = temp;

		if (count == 1)
		{
			return 0;
		}

		return aID(head -> next, toAdd, --count);
	}

	aID(head -> next, toAdd, count);		
}

int checker(node * head, int fData)
{
	if (!head)
	{
		return 0;
	}

	if (head -> data % fData == 0)
	{
		return checker(head -> next, fData) + 1;
	}
	else
	{
		checker(head -> next, fData);
	}
}
