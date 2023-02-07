// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// This file includes all of the pieces of the BST implementation

// Include the node implementation
#include "BSTNode.h"

// Include the dictionary ADT
#include "dictionary.h"
#include <string>
#include <stack>

#ifndef BST_H
#define BST_H

using namespace std;

// Binary Search Tree implementation for the Dictionary ADT
template <typename Key, typename E>
class BST : public Dictionary<Key, E> {
private:
	BSTNode<Key, E>* root;   // Root of the BST
	BSTNode<Key, E>* parent;

	int nodecount;         // Number of nodes in the BST

	// Private "helper" functions
	void clearhelp(BSTNode<Key, E>*);
	BSTNode<Key, E>* insertion(BSTNode<Key, E>*, const Key&, const E&);
	BSTNode<Key, E>* deletemin(BSTNode<Key, E>*);
	BSTNode<Key, E>* getmin(BSTNode<Key, E>*);
	BSTNode<Key, E>* removehelp(BSTNode<Key, E>*, const Key&);
	E* findhelp(BSTNode<Key, E>*, const Key&) const;
	void printhelp(BSTNode<Key, E>*, int) const;
	void vist(BSTNode<Key, E>*) const;

public:
	BST() { root = NULL; nodecount = 0; }  // Constructor

	//Note from Prof Sipantzi -- I've commented out the destructor
	//since you would have to change clearhelp() to make it work with
	//doubly-threaded trees and that is not part of the assignment.
	//~BST() { clearhelp(root); }            // Destructor

	void clear()   // Reinitialize tree
	{
		clearhelp(root); root = NULL; nodecount = 0;
	}

	// Insert a record into the tree.
	// k Key value of the record.
	// e The record to insert.
	void insert(const Key& k, const E& e) {
		root = insertion(root, k, e);
		nodecount++;
	}

	

	// Remove a record from the tree.
	// k Key value of record to remove.
	// Return: The record removed, or NULL if there is none.
	E* remove(const Key& k) {
		E* temp = findhelp(root, k);   // First find it
		if (temp != NULL) {
			root = removehelp(root, k);
			nodecount--;
		}
		return temp;
	}
	// Remove and return the root node from the dictionary.
	// Return: The record removed, null if tree is empty.
	E* removeAny() {  // Delete min value
		if (root != NULL) {
			E* temp = new E;
			*temp = root->element();
			root = removehelp(root, root->key());
			nodecount--;
			return temp;
		}
		else return NULL;
	}

	// Return Record with key value k, NULL if none exist.
	// k: The key value to find. */
	// Return some record matching "k".
	// Return true if such exists, false otherwise. If
	// multiple records match "k", return an arbitrary one.
	E* find(const Key& k) const { return findhelp(root, k); }

	// Return the number of records in the dictionary.
	int size() { return nodecount; }

	void print() const { // Print the contents of the BST
		if (root == NULL) cout << "The BST is empty.\n";
		else printhelp(root, 0);
		
	}

	// prints root in order
	void printInOrder() const {
		if (root == NULL)
			cout << "The Tree is empty!" << endl;
		else
			inOrder(root, nodecount);
	}

	void printReverse() const {
		if (root == NULL)
			cout << "The Tree is empty!" << endl;
		else
			reverseOrder(root, nodecount);
	}
};

// Visit -- prints out root
template <typename Key, typename E>
void BST<Key, E>::vist(BSTNode<Key, E>* r) const {
	cout << "Node - " << r->element() << endl;
}

// Clean up BST by releasing space back free store
template <typename Key, typename E>
void BST<Key, E>::
clearhelp(BSTNode<Key, E>* root) {
	if (root == NULL) return;
	clearhelp(root->left());
	clearhelp(root->right());
	delete root;
}

//Used https://algorithms.tutorialhorizon.com/double-threaded-binary-tree-complete-implementation/ for help on insertion
// Used https://www.geeksforgeeks.org/insert-a-node-in-binary-search-tree-iteratively/ for help on insertion
// Insert a node into the BST, returning the updated tree
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::insertion(BSTNode<Key, E>* root, const Key& k, const E& it) {
	if (root == NULL) {// Checks if the tree is empty
		BSTNode<Key, E>* child = new BSTNode<Key, E>(k, it, NULL, NULL); //Creates a child node
		if (parent == NULL) //Checks to see if the child has a parent node
			return child; //If there is no parent return the child node. 

		if (child->key()  < parent->key() ) { //Checks if the node is on the left or right 
			if(parent->left() ==NULL) //If the parents left node is null
				child->setLeft(parent); //Set the child node as the parent node
			else
				child->setLeft(parent->left()); //Otherwise set the node as the parents left child
			child->setRight(parent);
		}
		else {					
			if (parent->right() == NULL) //If the parents right node is null
				child->setRight(parent); //Set the child node as the parent node
			else
				child->setRight(parent->right()); //Otherwise se the node as the parents right child
			child->setLeft(parent);
		}
		return child;
	}
	parent = root; //Once the parent is determined set it equal to the root node
  if (k < root->key()) { //If the nodes key is less than the roots key
	  if (root->getLeftBit() == 1) { 
		  root->setLeft(insertion(NULL, k, it));
		  parent->setLeftBit(0);
	  }
	  else //Otherwise insert the root on the left
		  root->setLeft(insertion(root->left(), k, it));
  }
  else { //Otherwise if the key is greater than the roots key
	  if (root->getRightBit() == 1) { 
		  root->setRight(insertion(NULL, k, it));
		  root->setRightBit(0);
	  }
	  else //Insert the node on the right
		  root->setRight(insertion(root->right(), k, it));
  }
  return root;       //Return the node that was just inserted
}

// Delete the minimum value from the BST, returning the revised BST
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
getmin(BSTNode<Key, E>* rt) {
	if (rt->left() == NULL)
		return rt;
	else return getmin(rt->left());
}
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
deletemin(BSTNode<Key, E>* rt) {
	if (rt->left() == NULL) // Found min
		return rt->right();
	else {                      // Continue left
		rt->setLeft(deletemin(rt->left()));
		return rt;
	}
}

// Remove a node with key value k
// Return: The tree with the node removed
template <typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::
removehelp(BSTNode<Key, E>* rt, const Key& k) {
	if (rt == NULL) return NULL;    // k is not in tree
	else if (k < rt->key())
		rt->setLeft(removehelp(rt->left(), k));
	else if (k > rt->key())
		rt->setRight(removehelp(rt->right(), k));
	else {                            // Found: remove it
		BSTNode<Key, E>* temp = rt;
		if (rt->left() == NULL) {     // Only a right child
			rt = rt->right();         //  so point to right
			delete temp;
		}
		else if (rt->right() == NULL) { // Only a left child
			rt = rt->left();          //  so point to left
			delete temp;
		}
		else {                    // Both children are non-empty
			BSTNode<Key, E>* temp = getmin(rt->right());
			rt->setElement(temp->element());
			rt->setKey(temp->key());
			rt->setRight(deletemin(rt->right()));
			delete temp;
		}
	}
	return rt;
}

// Find a node with the given key value
template <typename Key, typename E>
E* BST<Key, E>::findhelp(BSTNode<Key, E>* root, const Key& k) const {
	if (root == NULL) return NULL;          // Empty tree
	if (k < root->key())
		return findhelp(root->left(), k);   // Check left
	else if (k > root->key())
		return findhelp(root->right(), k);  // Check right
	else {
		E* temp = new E;
		*temp = root->element();
		return temp;  // Found it
	}
}

// Print out a BST
template <typename Key, typename E>
void BST<Key, E>::printhelp(BSTNode<Key, E>* root, int level) const {
	if (root == NULL) return;           // Empty tree
	if (root->getLeftBit() == 0)
		printhelp(root->left(), level + 1);   // Do left subtree
	for (int i = 0; i < level; i++)         // Indent to level
		cout << "  ";
	cout << root->key() << "\n";        // Print node value
	if (root->getRightBit() == 0)
		printhelp(root->right(), level + 1);  // Do right subtree

}

//Function that prints out a BST in reverse order
//Used https://algorithms.tutorialhorizon.com/binary-tree-postorder-traversal-non-recursive-approach/ for help
template <typename Key, typename E>
void reverseOrder(BSTNode<Key, E>* root, int nodecount) {  
	stack<BSTNode<Key, E>* > s1;					
	stack<BSTNode<Key, E>* > s2;
	s1.push(root);

	while (s1.empty() == false) {
		BSTNode<Key, E>*  temp = s1.top(); s1.pop(); s2.push(temp);
		if (temp->getLeftBit() == NULL) {
			s1.push(temp->left());
		}
		if (temp->getRightBit() == NULL) {
			s1.push(temp->right());
		}
	}

	while (s2.empty() == false) {
		BSTNode<Key, E>*  temp = s2.top(); s2.pop();
		cout << temp->element() << endl;
	}
}

//Function that prints out a BST in order
//Used https://algorithms.tutorialhorizon.com/inorder-traversal-non-recursive-approach/ for help
template <typename Key, typename E>
void inOrder(BSTNode<Key, E>* root, int nodecount) { // In order print
	stack<BSTNode<Key, E>* > s; //New empty stack
	BSTNode<Key, E>*  current = root; //Sets the current node to the root node
	bool traversal = false; 
	while (traversal == false) //Loop to continue until the tree has been fully traversed
	{
		// if current node is not null, push it to the stack (defer it)
		// and move to its left child
		if (current->getLeftBit() == 0) { //If the current node equals zero
			s.push(current); //Push the current node onto the stack
			current = current->left(); //Current node now equals its left child node
		}
		else if (current->getRightBit() == 0) { //Else if the current right bit is equal to zero
			cout << current->element() << endl; //Output the current element
			nodecount--;
			current = current->right(); //Current node now equal its right child node
		}
		else { //If the current right and left bit equal 1
			if (current->getLeftBit() == 1 && current->getRightBit() == 1) {
				cout << current->element() << endl;
				nodecount--;
				current = s.top();
				cout << current->element() << endl;
				nodecount--;
				s.pop();
				current = current->right();
			}
			else {
				current = s.top();
				s.pop();
				cout << current->element() << endl;
				nodecount--;
				current = current->right();
			}
		}
		if (nodecount == 0) //Once the nodes have all been passed through
			traversal = true; //The tree has been traversed
	}
}

#endif