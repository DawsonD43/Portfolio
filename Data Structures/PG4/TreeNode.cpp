/*
	Dawson Dauphinais
	CS222, Data Structures
	Date Last Modified: 04/30/2020

	This file contains the functions of the TreeNode class.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include "TreeNode.h"
#include "DRT.h"
using namespace std;

TreeNode::TreeNode(string key, string data, TreeNode* l, TreeNode* r, TreeNode* p, Tree* T) {

	k = key; d = data; left = l; right = r; parent = p; t = T;
}

TreeNode::~TreeNode() { //destructor

	delete left;
	delete right;
}

DRT* TreeNode::add(string key, string data, string n, string p) {
	if (k == key) { // check if the key has been found
		DRT* temp = new DRT(data, n, p);
		d = data;   // d is overwritten and becomes the new value of "data'
		string next, prev;
		if (!right) next = n; // if there isn't a right child, next becomes n
		else next = right->first()->getk();   // next becomes the value of the node all the way to the right
		if (!left) prev = p;  // if there isn't a left child, prev becomes p            
		else prev = left->last()->getk();   // prev becomes the value of the node all the way to the left
		return temp;  // modify the DRT using the new value of Data
	}
	if (k < key) { // check to see if the value of k is less than the value of the key we are looking for
		if (right) { // check for a right child
			return right->add(key, data, n, k); // if there's a right child, use recursion to continue searching for the key
		}
		else { // there's no current right child
			right = new TreeNode(key, data, NULL, NULL, this, t); // create a new right child
			return new DRT("", n, k); // return a DRT, keeping track of pfs
		}
	}
	if (left) { // otherwise, check for a left child
		return left->add(key, data, k, p); // if there is a left child, use recursion to continue searching for the desired key
	}
	else {
		left = new TreeNode(key, data, NULL, NULL, this, t); // create a new left child if there is no left child
		return new DRT("", k, p); // return a DRT, keeping track of nsf
	}
}

/*searches for the node by keeping track of next-so-far and prev-so-far*/
DRT* TreeNode::searchnode(string key, string n, string p) {
	if (k == key) { // check if the key has been found
		string next, prev;
		if (!right) next = n; // if there isn't a right child, next becomes n
		else next = right->first()->getk(); // next becomes the value of the node all the way to the right 
		if (!left) prev = p; // if there isn't a left child, prev becomes p
		else prev = left->last()->getk(); // prev becomes the value of the node all the way to the left
		return new DRT(d, next, prev); // return a new DRT with the new values that have been modified
	}
	if (k < key) { // check to see if the value of k is less than the value of the key we are looking for
		if (right) return right->searchnode(key, n, k); // if there is a right child, use recursion to continue searching for the key
		return new DRT("", n, k); //k is now the psf
	}
	if (left) return left->searchnode(key, k, p); // if there is a left child, use recursion to continue searching for the key
	return new DRT("", k, p); // return new DRT keeping track of nsf

}

/*left all the way down*/
TreeNode* TreeNode::first() {
	if (left) return left->first(); // if there is a left child, use recursion to continue moving left
	else return this; // return the first node in the tree
}

/*right all the way down*/
TreeNode* TreeNode::last() { 
	if (right) return right->last(); // if there is a right child, use recursion to continue moving right
	else return this; // return the last node in the tree
}

string TreeNode::getk() { return k; }

string TreeNode::getd() { return d; }

TreeNode* TreeNode::getright() { return right; }

TreeNode* TreeNode::getleft() { return left; }

/*right once, left all the way down*/
string TreeNode::next() { // right once, left all the way down. makes use of first()
	return getright()->first()->getk();
}
/*left once, right all the way down*/
string TreeNode::prev() {
	return getleft()->last()->getk();
}

/*searches for node to remove, and then passes that node on*/
DRT* TreeNode::remove(string key, string n, string p) {
	//similar to search; keeps track of nsf and psf
	 //just works its way down the tree to find the node to remove
	 //then calls remove ()
	if (k == key) {          // check to see if the key has been found
		string next, prev;
		if (!right) next = n; // if there is no right child, set next equal to n
		else next = right->first()->getk(); // next becomes the value of the node all the way to the right
		if (!left) prev = p;  // if there is no left child, set prev equal to p
		else prev = left->last()->getk(); // prev becomes the value of the node all the way to the left
		DRT* temp = new DRT(this->getd(), next, prev);
		this->remove(); // call remove on the node that matches the key
		return temp; // return a new DRT with modified values
	}
	if (k < key) {  // 
		if (right) return right->remove(key, n, k); // if there is a right child, use recursion to continue searching for the node.
		return new DRT("", n, k); // return a DRT keeping track of psf
	}
	if (left) return left->remove(key, k, p); // if there is a left child, use recursion to continue searching for the node
	return new DRT("", k, p); // return a DRT keeping track of nsf
}

/*deletes the node*/
void TreeNode::remove() {
	                           //the physical removal (decides whether it's 0, 1, or 2-child case and possibly copies key and data values and physically removes the deleted node
	if (!left && !right) {	   // check if I'm left or right child of parent / 0 child case
		if (parent == NULL) {  // check to see if the node to be removed is the root node
			t->setroot(NULL);  // if it is the root node, set root to NULL
			left = NULL;       // set the left node's pointer to NULL
			right = NULL;      // set the right node's pointer to NULL
			delete this;       // delete the node
		}
		else if (parent->getleft() == this) {  // check to see if the node to be deleted is a left child
			parent->setleft(NULL);             // set the left node's parent to NULL
			left = NULL;					   // set the left node's pointer to NULL
			right = NULL;					   // set the right node's pointer to NULL
			delete this;					   // delete the node 
		}
		else if (parent->getright() == this) { // check to see if the node to be deleted is a right child
			parent->setright(NULL);			   // set the right child's parent to NULL
			left = NULL;					   // set the left node's pointer to NULL
			right = NULL;					   // set the right node's pointer to NULL
			delete this;					   // delete the node 
		}
	}
	else if ((!left && right) || (left && !right)) { // either a left or right child / 1-child case
		if (parent == NULL) {                        // check to see if the node is the root
			if (right) {                             
				t->setroot(right);                   // if the root has a right child, set the root to it's right child.
				right->setparent(NULL);              // then set the right child's parent to NULL
			}
			else {
				t->setroot(left);					 // if the root has a left child, set the root to it's left child,
				left->setparent(NULL);				 // then set the left child's parent to NULL
			}
			left = NULL;                             // set the left node's pointer to NULL
			right = NULL;							 // set the right node's pointer to NULL
			delete this;							 // delete the node
		}
		else if (parent->getleft() == this) { // check to see if the node to be deleted is the left child of its parent node
			if (left) {                       // check to see if the node to be deleted has a left child
				left->setparent(parent);      // set the left child's parent to the current node's parent
				parent->setleft(left);        // set the parent node's new left child to the left child of the node to be deleted
			}
			else if (right) {                 // check to see if the node to be deleted has a right child
				right->setparent(parent);     // set the right child's parent to the current node's parent
				parent->setleft(right);       // set the parent node's new left child to the right child of the node to be deleted
			}
			left = NULL;                      // set the left node's pointer to NULL
			right = NULL;                     // set the right node's pointer to NULL
			delete this;                      // delete the node
		}
		else if (parent->getright() == this) { // check to see if the node to be deleted is the right child of its parent node
			if (left) {                        // check to see if the node to be deleted has a left child
				left->setparent(parent);       // set the left child's parent to the current node's parent
				parent->setright(left);        // set the parent nodes' new right child to the left child of the node to be deleted
			}
			else if (right) {                  // check to see if the node to be deleted has a right child
				right->setparent(parent);      // set the right child's parent to the current node's parent
				parent->setright(right);       // set the parent node's new right child to the right child of the node to be deleted
			}              
			left = NULL;                       // set the left node's pointer to NULL
			right = NULL;                      // set the right node's pointer to NULL
			delete this;                       // delete the node
		}
	}
	else if (left && right) {						// if the node has 2 children
		TreeNode* temp = this->getright()->first(); // make a copy of current node and move to the right once, and then left all the way down
		k = temp->getk();							// set the new k value as the k value found from the next node
		d = temp->getd();							// set the new d value as the d value found from the next node
		temp->remove();								// delete the next node
	}
}

void TreeNode::setparent(TreeNode* p) { parent = p; }
void TreeNode::setleft(TreeNode* l) { left = l; }
void TreeNode::setright(TreeNode* r) { right = r; }

