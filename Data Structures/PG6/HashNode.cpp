/*
	Dawson Dauphinais
	CS222, Data Structures
	Date Last Modified: 04/24/2020

	This file contains the functions of the HashNode class, allowing for the manipulation of nodes within a hashtable.
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include "HashNode.h"
#include "DRT.h"
using namespace std;

/*HashNode constructor*/
HashNode::HashNode(string key, string data) {

	k = key; d = data; next = NULL;
}

/*destructor*/
HashNode::~HashNode() {

	delete next;
}

/*searches for the node*/
DRT* HashNode::searchnode(string key) {

	if (k == key) {
		return new DRT(d, "", "");	// if the key is found, update data inside the DRT
	}
	if (!next) {
		return new DRT("", "", ""); // if the key isn't found, return a new DRT with no data updated
	}
	return next->searchnode(key);   // if neither case is true, use recursion to continue searching for the key
}
/*updates the number of entries by updating the DRT*/
DRT* HashNode::addnode(string key, string data) {

	if (k == key) {
		d = data;													 // change the value of d to be the data of the current key
		return new DRT(d, "", "");									 // if the key is found, update the DRT with the new data
	}				
	if (!next) {													 // check to see if there isn't a next node
		next = new HashNode(key, data);								 // create a new next node
		return new DRT("", "", "");									 // return a new DRT
	}
	return next->addnode(key, data);								 // if neither case is true, call recursion to continue searching
}
/*return the value of k*/
string HashNode::getk() { return k; }

/*return the value of d*/
string HashNode::getd() { return d; }

/*searches for the node to remove and then removes it*/
DRT* HashNode::remove(string key, HashNode* p, HashNode*& listhead) {
	if (k == key) {														// check if the key is found
		DRT* temp = new DRT(this->getd(), "", "");						// create a temporary DRT so this's data doesn't get lost
		if (next) {													    // check to see if the current node has a next
			if (!p) {													// check if the current node's previous is NULL
				listhead = next;										// if previous is null, next node becomes the new listhead
				p = NULL;												// make sure previous is set to NULL
				next = NULL;										    // set next's pointer to NULL 
				delete this;											// delete the node
				return temp;											// return the DRT with the data of the node that got deleted
			}
			else {														// check if there isn't a previous node
				listhead = p;											// previous becomes the new listhead
				p->setnext(next);										// move p's next pointer to point to the current node's next
				next = NULL;											// make sure next points to NULL
				delete this;											// delete the node
				return temp;											// return the DRT with the data of the node that got deleted
			}
		}
		else {															// if there is no next node
			if (!p) {													// check to see if previous is NULL
				this->setnext(NULL);									// set the current node's next pointer to NULL
				listhead = NULL;										// the list head now becomes NULL because the list is empty
				next = NULL;											// set next to point to NULL
				delete this;											// delete the current node
				return temp;											// return the DRT with the data of the node that got deleted
			}
			else {														// if the current node does have a previous
				listhead = p;											// the listhead becomes the previous node
				p->setnext(NULL);										// set p's next to point to NULL
				next = NULL;											// make sure that next is NULL
				delete this;											// delete the current node
				return temp;											// return the DRT with the data of the node that go deleted
			}
		}
	}
	else {
		return next->remove(key, this, listhead);						// if the key hasn't been found, use recursion continue searching.
	}
}

/*set the next node*/
void HashNode::setnext(HashNode* p) { next = p; }

