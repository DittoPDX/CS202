/*
Steven Tran
CS202 | Program #3
Karla Fant
2/12/2017

This is the header file for the emergency broadcast system class which contains
the prototypes which manages all of the groups using a balanced binary
search tree. The balanced tree implementation is the AVL tree. The tree node class
"is a" group which allows it to control the sorted linear linked list of a
particular last name group. Then the overall "Table ADT" is just the binary
search tree or AVL tree.
*/

#include "Group.h"

using namespace std;

class tnode: public group
{
	public:
		tnode();
		tnode(const group & src);
		tnode(const tnode & src);

		tnode & operator = (const tnode & src);	
	
		void set_left(tnode * connect);
		void set_right(tnode * connect);
		void set_height(int height);

		int get_height(tnode * root);
		tnode *& go_left();
		tnode *& go_right();
			
	protected:
		tnode * left;
		tnode * right;
		int height;
};

class binary_tree	
{
	public:
		binary_tree();	
		binary_tree(const binary_tree & src);
		
		binary_tree & operator = (const binary_tree & src);

		~binary_tree();
		int display() const;
			
	protected:
		tnode * root;

		int copy_tree(tnode *& dest, tnode * src);
		int clear_all(tnode *& root);
		int display_all(tnode * root) const;	
};

//Doesn't manage dynamic data, so no copy constructor.
class BST : public binary_tree
{
	public:
		BST();
			
		int add(const group & to_add);

	protected:
		int balance_factor;
		tnode * add(tnode * root, const group & to_add);
		tnode * left_rotate(tnode * parent);
		tnode * right_rotate(tnode * parent);
		int check_balance(tnode * root);
		int update_height(tnode *& root);
		tnode * balance(int factor, tnode * root);
};

//No copy constructor because no dynamic data as well.
class system : public BST
{
	public:
		system();
		int add(const group & to_add);
		int add_person(const char * group_name, const person & to_add);
		int display() const;
		int find(group & to_find);
		int find(char * to_find, group & temp);
		int find_person(const char * to_find, char *& if_found, char **& contacts);
		int remove_person(const char * group_name, const char * person_name);
		int remove_everyone_group(const char * group_name);
	
		//Assignment requires that we implement these operators.
		system & operator = (const system & src);
		//+ doesn't make sense with this class.
		//system operator + (const group & to_add);
		system & operator += (const group & to_add);
	
		bool operator != (const group & to_compare);
		bool operator == (const group & to_compare);
		friend bool operator == (system & ebs, const char * name);
		
		//>> doesn't make sense with this class.
		//friend istream & operator >> (istream & is, group & to_add);
		friend ostream & operator << (ostream & os, const system & src);

	protected:
		int add_person(tnode * root, const char * group_name, const person & to_add);
		bool compare_group(tnode * root, const group & to_compare);
		int display_all(tnode * root) const;
		int find(tnode * root, group & to_find);
		int find(tnode * root, char * to_find, group & temp);	
		int find_person(tnode * root, const char * to_find, char *& if_found, char **& contacts);
		int remove_person(tnode * root, const char * group_name, const char * person_name);
		int remove_everyone_group(tnode * root, const char * group_name);
		bool verify(tnode * root, const group & to_verify);
		bool verify_name(tnode * root, const char * name);
};
