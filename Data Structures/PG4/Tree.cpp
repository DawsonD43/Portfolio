/*
	Dawson Dauphinais
	CS222, Data Structures
	Date Last Modified: 04/22/2020

	This file contains the logic for manipulating a binary tree (AVL).
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <assert.h>
#include "Tree.h"
#include "DRT.h"
#include "TreeNode.h"
using namespace std;

Tree::Tree() { root = NULL; }

Tree::~Tree() { delete root; }

void Tree::setroot(TreeNode* r) { root = r; }

/*add to the tree*/
DRT* Tree::add(string key, string data) { //very similar to sample code

	if (!root) { // check to see if there's no root node
		root = new TreeNode(key, data, NULL, NULL, NULL, this); // if there's no root node, create a new node and set it as the root node
		return new DRT("", "", ""); // return a DRT
	}
	return root->add(key, data, "", ""); // if there is a root node, call the add method found in TreeNode.cpp on root
}

/*searches the tree for the given key*/
DRT* Tree::searchnode(string key) { 
	if (root)  // check to see if there is a root node
		return root->searchnode(key, "", ""); // if there's a root node, recursively call the searchnode method found in TreeNode.cpp
	else
		return new DRT("", "", "");           // if there's no root node, the key doesn't exist in the tree, return a DRT
}

/*get's the first key in the tree (left all the way down)*/
string Tree::first() { 
	if (root == NULL) return NULL;
	else return root->first()->getk();
}

/*last key in the tree (right all the way down)*/
string Tree::last() {
	if (root == NULL) return NULL; // if root is null, return NULL as there are no right children
	else return root->last()->getk(); // otherwise use recursion on root to get the last node and it's k value
}

/*removes an item from the list*/
DRT* Tree::remove(string key) { //removes an item from the list
	if (root) return root->remove(key, "", "");
	else return new DRT(key, "", "");
}

/*Database search method*/
DRT* Tree::search(string key) { 
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
DRT* Tree::modify(string key, string data) { 
	if (key == "") return new DRT("", first(), last());
	if (data == "") return remove(key);
	return add(key, data);
}