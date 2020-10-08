/*
	Dawson Dauphinais
	CS222, Data Structures
	Date Last Modified: 04/28/2020

	This file contains the functions that allow for the manipulation of red-black trees.
*/
#include <cstdlib>
#include "RBTreeNode.h"
#include "DRT.h"
#include "Database.h"
#include "RBTree.h"
using namespace std;

/*constructor*/
RBTree::RBTree() { root = NULL; }

/*destructor*/
RBTree::~RBTree() { delete root; }

/*add to the tree*/
DRT* RBTree::add(string key, string data) { //very similar to sample code
	if (!root) { // check to see if there's no root node
		root = new RBTreeNode(key, data, NULL, NULL, NULL, this); // if there's no root node, create a new node and set it as the root node
		root->AddProcess();
		return new DRT("", "", ""); // return a DRT
	}
	return root->add(key, data, "", ""); // if there is a root node, call the add method found in RBTreeNode.cpp on root
}

/*set root*/
void RBTree::setroot(RBTreeNode* r) { root = r; }


/*searches the tree for the given key*/
DRT* RBTree::searchnode(string key) { //searches the RBTree for the given key
	if (root)  // check to see if there is a root node
		return root->searchnode(key, "", ""); // if there's a root node, recursively call the searchnode method found in RBTreeNode.cpp
	else
		return new DRT("", "", "");           // if there's no root node, the key doesn't exist in the tree, return a DRT
}

/*first key in the RBTree (left all the way down)*/
string RBTree::first() {
	if (!root) return NULL;
	else return root->first()->getk();
}

/*last key in the RBTree (right all the way down)*/
string RBTree::last() {
	if (!root) return NULL; // if root is null, return NULL as there are no right children
	else return root->last()->getk(); // otherwise use recursion on root to get the last node and it's k value
}

/*removes an item from the list*/
DRT* RBTree::remove(string key) {
	if (root) return root->remove(key, "", "");
	else return new DRT(key, "", "");
}

/*Database search method*/
DRT* RBTree::search(string key) {
	//checks to see if we're searching on the empty string, if so builds a DRT with first() and last (), otherwise calls searchnode
	string data, next, prev;
	if (key == "") { // check to see if searchin on the empty string
		data = "";   // set data equal to the empty string
		if (root) {  // check to see if there is a root node
			next = root->first()->getk();  // if there is a root node, set next equal to the k value of the first node in the tree
			prev = root->last()->getk();   // set prev equal to the k value of the last node in the tree
			return new DRT(data, next, prev); // return a DRT
		}
		else return new DRT(data, "", ""); // if there is no root, return a DRT without changing next and prev values
	}
	else { // if not searching on the empty string, call the searchnode method found in TreeNode.cpp
		return searchnode(key);
	}
}

/*Database modify method*/
DRT* RBTree::modify(string key, string data) {
	if (key == "") return new DRT("", first(), last());
	if (data == "") return remove(key);
	return add(key, data);
}

int RBTree::Valid() {

	int r;

	if (!root) {
		r = 1;
	}
	else {
		if (!root->isblack() || root->getparent()) {
			r = 0;
		}
		else {
			r = root->ValidNode() != -1;
		}
	}
	return r;
}