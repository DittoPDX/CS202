/*
Steven Tran
CS202 | Program #3
Karla Fant
2/12/2017

This is the implementation .cpp file for the binary search tree or emergency
broadcast system which contains all of the functions required to manage each
individual group. The groups in the tree are sorted by last name. The
balanced tree implemented in this .cpp file is the AVL tree. Guarantees
O(log(n)) efficiency in time complexity for access, retrieval, and adding etc.
*/

#include "System.h"

//Initializes all data members to 0.
tnode::tnode() : left(NULL), right(NULL), height(0)
{

}

//Copies the group into the current data.
tnode::tnode(const group & src) : group(src)
{

}

//Copies the node ("a group") into the current data.
tnode::tnode(const tnode & src) : group(src)
{

}

//Assignment operator to copy one group to the other.
tnode & tnode::operator = (const tnode & src)
{
	if (this == & src) return * this;

	group::operator=(src);

	left = src.left;
	right = src.right;

	return * this;
}

//Connect the left pointer of a tree node.
void tnode::set_left(tnode * connect)
{
	this -> left = connect;
}

//Connect the right pointer of a tree node.
void tnode::set_right(tnode * connect)
{
	this -> right = connect;
}

//Set the height specified for a tree node.
void tnode::set_height(int height)
{
	this -> height = height;
}

//Used to determine heights for the balancing algorithm.
int tnode::get_height(tnode * root)
{
	if (!root) return 0;

	return root -> height;
}

//Go left in a tree.
tnode *& tnode::go_left()
{
	return left;
}

//Go right in a tree.
tnode *& tnode::go_right()
{
	return right;
}

//Set the root to NULL when an instance of binary tree is created.
binary_tree::binary_tree() : root(NULL)
{

}

//Copy constructor to create a new BST object.
binary_tree::binary_tree(const binary_tree & src)
{
	copy_tree(root, src.root);
}

//Helper recursive function to copy a tree for the copy constructor.
int binary_tree::copy_tree(tnode *& dest, tnode * src)
{
	if (!src) return 0;
	
	dest = new tnode(*src);
	dest -> set_left(NULL); dest -> set_right(NULL);
	
	return copy_tree(dest -> go_left(), src -> go_left()) +
	       copy_tree(dest -> go_right(), src -> go_right());
}

//Assignment operator to copy data values into an existing tree.
binary_tree & binary_tree::operator = (const binary_tree & src)
{
	if (this == &src) return * this;

	if (root)
	{
		clear_all(root);
	}

	copy_tree(root, src.root);

	return * this;
}

//Destructor to clear all dynamic memory.
binary_tree::~binary_tree()
{
	if (root)
	{
		clear_all(root);
	}
}

//Helper recursive function to help clear all dynamic memory.
int binary_tree::clear_all(tnode *& root)
{
	if (!root) return 0;

	clear_all(root -> go_right());
	clear_all(root -> go_left());

	delete root;
	root = NULL;
	return 1;
}

//Display all nodes in a BST.
int binary_tree::display() const
{
	if (!root)
	{
		cout << "Nothing to display." << endl;
		return 1;
	}
	
	return display_all(root);
}

//Displays all of the people in the group category recursively.
int binary_tree::display_all(tnode * root) const
{
	if (!root) return 0;

	display_all(root -> go_left());
	root -> display();
	return display_all(root -> go_right());		
}

//Set the balance factor to 0 for the AVL tree.
BST::BST() : balance_factor(0)
{
	
}

//Helps update the height for adding nodes.
int BST::update_height(tnode *& root)
{
	if (!root) return 0;

	root -> set_height(1 + max(root -> get_height(root -> go_left()), root -> get_height(root -> go_right())));

	return 1;
}

//AVL add implementation for the tree.
int BST::add(const group & to_add)
{
	root = add(root, to_add);
	return 1;
}

//Ultimate recursive function to balance the tree while adding.
tnode * BST::add(tnode * root, const group & to_add)
{
	if (!root)
	{
		root = new tnode(to_add);
		root -> set_height(1);
		root -> set_left(NULL); root -> set_right(NULL);

		//After returning root, the height
		//should update in the code below the else statement.
		return root;
	}
	else if (root -> compare(to_add) > 0)
	{
		root -> set_left(add(root -> go_left(), to_add));
	}
	else
	{
		root -> set_right(add(root -> go_right(), to_add));
	}

	/*
	//Right rotation
		a         	    b
	       /		   / \
	      b        becomes    c   a
	     /
	    c	

	//Right-Left rotation
		a		    a     		   c
	       	 \		     \                    / \
		  b    becomes        c        becomes   a   b
		 /		       \
		c			b

	//Left rotation
		a		    b
		 \		   / \
		  b    becomes    a   c
		   \
		    c

	//Left-Right rotation
		a		    a 			  c
	       /		   / 			 / \
	      b        becomes    c           becomes   b   a
	       \		 /
   		c		b
	*/

	return balance(balance_factor, root);
}

//The balancing function for the four cases above in the recursive add function.
tnode * BST::balance(int factor, tnode * root)
{
	//Update bottom-most to top-most nodes of a tree.
	update_height(root);

	//Check to see if balance factor is greater than 1 or less than -1.
	balance_factor = check_balance(root);

	if (balance_factor > 1)
	{
		//Rotate the middle node to the left and then rotate root node to the right.
		if (check_balance(root -> go_left()) < 0)
		{
			//cout << "LR" << endl;
			tnode * temp = root -> go_left();
			root -> set_left(left_rotate(temp));
			return right_rotate(root);	
		}
	
		//Rotate to the right.	
		if (check_balance(root -> go_left()) > 0)
		{	
			//cout << "single right rotate" << endl;
			return right_rotate(root);
		}	
	}
	else if (balance_factor < -1)	
	{
		//Rotate middle node to the right and then rotate root to the left.
		if (check_balance(root -> go_right()) > 0)
		{
			//cout << "RL" << endl;
			tnode * temp = root -> go_right();
			root -> set_right(right_rotate(temp));
			return left_rotate(root);
		}
	
		//Rotate to the left.	
		if (check_balance(root -> go_right()) < 0)
		{
			//cout << "rotated single left" << endl;
			return left_rotate(root);
		}
		
	}

	return root;
}

//The left rotate case for the AVL tree insertion.
tnode * BST::left_rotate(tnode * parent)
{
	tnode * right_child = parent -> go_right();
	tnode * left_of_right_child = right_child -> go_left();

	//Move the right_child up and the parent down.	
	right_child -> set_left(parent);
	parent -> set_right(left_of_right_child);	
	
	//Update heights
	update_height(parent);
	update_height(right_child);

	return right_child;
}

//The right rotate case for the AVL tree insertion.
tnode * BST::right_rotate(tnode * parent)
{
	tnode * left_child = parent -> go_left();
	tnode * right_of_left_child = left_child -> go_right();

	//Move the left child up and the parent down.
	left_child -> set_right(parent);
	parent -> set_left(right_of_left_child);

	//Update heights
	update_height(parent);
	update_height(left_child);

	return left_child;
}

//Used to determine if the subtrees are valid for an AVL tree.
int BST::check_balance(tnode * root)
{
	if (!root) return 0;

	return root -> get_height(root -> go_left()) - root -> get_height(root -> go_right());
}

//The default constructor for the system class.
system::system() : BST()
{
	
}

//Add a group to the tree.
int system::add(const group & to_add)
{
	return BST::add(to_add);
}

//Display all of the groups and their people on the tree.
int system::display() const
{
	return display_all(root);	
}

//Displays group name and everyone inside it.
int system::display_all(tnode * root) const
{
	if (!root) return 0;

	display_all(root -> go_left());
	root -> display_name(); cout << endl;
	root -> display();
	cout << endl;
	return display_all(root -> go_right());
}

//Find a particular group in the AVL tree.
int system::find(group & to_find)
{
	if (!root) return -1;

	return find(root, to_find);
}

//Helper recursive function for finding a group in an AVL tree.
int system::find(tnode * root, group & to_find)
{
	if (!root) return 0;

	if (root -> compare(to_find) == 0)
	{
		return 1;
	}

	return find(root -> go_left(), to_find) +
	       find(root -> go_right(), to_find);
}

//Finding the group then copy the group (node) to a temporary.
int system::find(char * to_find, group & temp)
{
	if (!to_find) return 0;

	return find(root, to_find, temp);
}

//Helper recursive function to help copy the group into a temporary.
int system::find(tnode * root, char * to_find, group & temp)
{
	if (!root) return 0;
	
	if (root -> compare(to_find) == 0)
	{
		temp = *root;
		return 1;
	}

	return find(root -> go_left(), to_find, temp) +
	       find(root -> go_right(), to_find, temp);
}

//Find a person in a group.
int system::find_person(const char * to_find, char *& if_found, char **& contacts)
{
	if (!to_find || !root) return 0;

	return find_person(root, to_find, if_found, contacts);
}

//Recursive function for finding a person in one of the groups in the tree.
int system::find_person(tnode * root, const char * to_find, char *& if_found, char **& contacts)
{
	if (!root) return 0;

	if (root -> find(to_find, if_found, contacts) == 1)
	{
		return 1;
	}

	return find_person(root -> go_left(), to_find, if_found, contacts) +
	       find_person(root -> go_right(), to_find, if_found, contacts);
}

//Assignment operator to copy one tree to another (or one system to another).
system & system::operator = (const system & src)
{
	if (this == &src) return * this;

	if (root) 
	{
		clear_all(root);
	}

	copy_tree(root, src.root);

	return * this;
}


//Doesn't make sense with this class overall.
/*
istream & operator >> (istream & is, group & to_add)
{
	is >> to_add;
	return is;	
}
*/

//Overloading the extraction operator to display the tree.
ostream & operator << (ostream & os, const system & src)
{
	src.display();
	return os;
}

/*
"You may find that some operators don't apply at all (and therefore shouldn't
be implemented."
Doesn't quite make sense for us to simply add and return a class by value...

system system::operator + (const group & to_add)
{
	system temp;
	temp.add(to_add);

	return temp;
}
*/

//Makes more sense to simply update the system by reference.
system & system::operator += (const group & to_add)
{
	add(to_add);
	return * this;	
}

//Checks if one group is not the same as another.
bool system::operator != (const group & to_compare)
{
	if (!root) return false;

	return compare_group(root, to_compare);	
}

//Checks if one group is not the same as another (recursive helper function).
bool system::compare_group(tnode * root, const group & to_compare)
{
	if (!root) return false;

	if (root -> compare(to_compare) != 0)
	{
		return true;
	}

	return compare_group(root -> go_left(), to_compare) + 
	       compare_group(root -> go_right(), to_compare);
}

//Checks if one group is the same as the other.
bool system::operator == (const group & to_compare)
{
	if (!root) return false;

	return verify(root, to_compare);
}

//Recursive helper function for checking if one group is the same as the other.
bool system::verify(tnode * root, const group & to_verify)
{
	if (!root) return false;
		
	if (root -> compare(to_verify) == 0)
	{
		return true;
	}

	return verify(root -> go_left(), to_verify) + 
	       verify(root -> go_right(), to_verify);
}

//"Wrapper" function for checking if group name matches a group on the tree.
bool operator == (system & ebs, const char * name)
{
	if (!ebs.root) return false;

	return ebs.verify_name(ebs.root, name);
}

//Recursive function for checking if group name matches a group on the tree.
bool system::verify_name(tnode * root, const char * name)
{
	if (!root) return false;

	if (root -> compare(name) == 0)
	{
		return true;
	}

	return verify_name(root -> go_left(), name) +
	       verify_name(root -> go_right(), name);
}

//Wrapper function for adding a preson to an existing group on the tree.
int system::add_person(const char * group_name, const person & to_add)
{
	if (!group_name) return 0;

	return add_person(root, group_name, to_add);
}

//Recursive function for adding a person to an existing group on the tree.
int system::add_person(tnode * root, const char * group_name, const person & to_add)
{
	if (!root) return 0;
	
	if (root -> compare(group_name) == 0)
	{
		root -> add_person(to_add);
	}

	return add_person(root -> go_left(), group_name, to_add) +
	       add_person(root -> go_right(), group_name, to_add);
}

//Wrapper function for removing a single person from a specified group.
int system::remove_person(const char * group_name, const char * person_name)
{
	if (!group_name || !person_name || !root) return 0;

	return remove_person(root, group_name, person_name);
}

//Recursive function for removing a single person from a specified group.
int system::remove_person(tnode * root, const char * group_name, const char * person_name)
{
	if (!root) return 0;

	if (root -> compare(group_name) == 0)
	{
		int success = root -> remove(person_name);
		return success;
	}

	return remove_person(root -> go_left(), group_name, person_name) +
	       remove_person(root -> go_right(), group_name, person_name);
}

//Wrapper function for removing everyone in a group.
int system::remove_everyone_group(const char * group_name)
{
	if (!group_name || !root) return 0;

	return remove_everyone_group(root, group_name);
}

//Recursive function for removing everyone in a group.
int system::remove_everyone_group(tnode * root, const char * group_name)
{
	if (!root) return 0;

	if (root -> compare(group_name) == 0)
	{
		root -> remove_all();
		return 1;
	}

	return remove_everyone_group(root -> go_left(), group_name) +
	       remove_everyone_group(root -> go_right(), group_name);
}
