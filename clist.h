//clist.h
//All solutions were done recursively.

#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

struct node
{
    int data;
    node * next;
};

/* These functions are already written and can be called to test out your code */
void build(node * & rear);  //supplied
void display(node * rear);  //supplied
void destroy(node * & rear); //supplied

/* *****************YOUR TURN! ******************************** */
//Write your function prototype here:

/*DISPLAY QUESTIONS */
int displayAll(node * head);
int dA(node * head);

int displayReverse(node * head);
int dR(node * head);

int displayDivisible(node * head, int toDisplay);
int dD(node * head, int toDisplay);

int displayEveryOther(node * head);
int dEO(node * head);

/*ADD QUESTIONS */
int addToEnd(node *& head);
int returnSum(node * head);

int addAfter2(node *& head, int toAdd);
int ADDAF2(node *& head, int toAdd);

int addBefore2(node *& head, int toAdd);
int ADDBF2(node *& head, int toAdd);

/*HARD QUESTIONS*/
int modifyAfter(node *& head);
int mA(node *& head, int fData);

//This was the hardest problem
int reverseAll(node *& head);
node * rA(node * head);
int rA2(node *& head);

int appendIfDivisible(node *& head, int toAdd);
int aID(node *& head, int toAdd, int count);
int checker(node * head, int fData);
