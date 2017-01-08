#include "clist.h"
using namespace std;

int main()
{
    node * rear = NULL;
    build(rear);
    display(rear);
/*
    //PLEASE PUT YOUR CODE HERE to call the function assigned
    int items = displayAll(rear);
    cout << "|Number of items: " << items << endl;

    int items2 = displayReverse(rear);
    cout << "|Number of items: " << items2 << endl;

    int items3 = displayDivisible(rear, 2);
    cout << "|Number of items: " << items3 << endl;

    int items4 = displayEveryOther(rear);
    cout << " |Number of items: " << items4 << endl;

    int items5 = addToEnd(rear);
    cout << "Total sum: " << items5 << endl;

    int items6 = addAfter2(rear, 99);
    cout << "Number of nodes added after 2s: " << items6 << endl;

    int items7 = addBefore2(rear, 80);
    cout << "Number of nodes added before 2s: " << items7 << endl;

    int items8 = modifyAfter(rear);
    cout << "Number of nodes added after divisible 3/5: " << items8 << endl;

    int items9 = reverseAll(rear);
    cout << "Number of nodes reversed: " << items9 << endl;
*/

    int items10 = appendIfDivisible(rear, 100);
    cout << "Number of nodes appended: " << items10 << endl;	

    display(rear); //resulting list after your function call!
    destroy(rear);
    
    return 0;
}
