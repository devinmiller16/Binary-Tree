//<Devin_Miller_Binary_Tree_Assignment> -- This program is designed to implement a double-threaded BST using a stack and dictionary
//CSIS 215-<D02>
//<Citations if necessary> -- citations are required
//  https://algorithms.tutorialhorizon.com/binary-tree-postorder-traversal-non-recursive-approach/ Used for reverse order tree traversals
//  https://algorithms.tutorialhorizon.com/inorder-traversal-non-recursive-approach/ Used for in order tree traversals
//  https://algorithms.tutorialhorizon.com/double-threaded-binary-tree-complete-implementation/ Used for insertion helper and in order/reverse order traversals
//  https://stackoverflow.com/questions/13272527/implement-a-stack-using-a-bst Used for stack implementation using BST
//  https://www.geeksforgeeks.org/insert-a-node-in-binary-search-tree-iteratively/ Used for insertion help

#include <string>
#include <sstream>
#include <iostream>
#include "BST.h"

using namespace std;

void PauseScreen(); //Used to pause the screen output

int main() {

	cout << "Devin Miller - Assignment#2" << endl << endl;

	BST<int, string> *Tree = new BST<int, string>; //Creates a new BST pointer object

	cout << "Testing the insert function to build my tree." << endl;
	cout << "Before insertion my BST tree size is " << Tree->size() << endl;
	//BST Node insertion
	Tree->insert(77, "seventy-seven"); 
	Tree->insert(70, "seventy");
	Tree->insert(75, "seventy-five");
	Tree->insert(66, "sixty-six");
	Tree->insert(79, "seventy-nine");
	Tree->insert(68, "sixty-eight");
	Tree->insert(67, "sixty-seven");
	Tree->insert(69, "sixty-nine");
	Tree->insert(90, "ninety");
	Tree->insert(85, "eighty-five");
	Tree->insert(83, "eighty-three");
	Tree->insert(87, "eighty-seven");
	Tree->insert(65, "sixty-five");
	cout << "After inserting objects into my tree, my tree's structure is: " << endl;
	Tree->print(); //BST Print function
	cout << "My BST tree size is " << Tree->size() << endl;
	cout << endl << endl;

	if (Tree->size() == 0) { //If the BST is empty
		cout << "The Tree is empty..." << endl;
		cout << "Exiting program!" << endl;
	}
	else { //If there are objects in the BST
		cout << "Inorder printing of my tree" << endl;
		Tree->printInOrder(); //Print the in order function 
		cout << endl << endl;
		cout << "Reverse order printing of my tree" << endl;
		Tree->printReverse(); //Print the reverse order function
	}
	


	PauseScreen();

	return 0;
}

//Used to pause the screen wherever desired
void PauseScreen()
{
	char ch;
	cout << "\nPress the Enter key to continue ... ";
	cin.get(ch);
}