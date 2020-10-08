/*
	Dawson Dauphinais
	CS222, Data Structures
	Date Last Modified: 04/24/2020

	This file implements the functions of the HashTable class, allowing for the manipulation of a hashtable.
*/

#include <iostream>/
#include <string>
#include <cstdlib>
#include "HashTable.h"
#include "DRT.h"
#include "Database.h"
#include "HashNode.h"
using namespace std;

/*generates a HashTable with the given size*/
HashTable::HashTable(int sz) {

	HS = sz;
	table = new HashNode * [HS];
	for (int i = 0; i < HS; i++)
		table[i] = NULL; // initialize each element in the array to NULL
}

/*destructor*/
HashTable::~HashTable() {
	for (int i = 0; i < HS; i++)
		delete table[i];
	delete[] table;
}

/*hashes the given key*/
int HashTable::hf(string key) {

	int val = 0;
	for (int i = 0; i < key.length(); i++) {
		int ch = key[i];
		if (ch == 0) ch = 256;
		val = (val * 256 + ch) % HS;
	}
	return val;
}

/*adds a new entry to the HashTable (key,data)*/
DRT* HashTable::add(string key, string data) { 
	int val = hf(key); 
	if (!table[val]) {								// check to see if there is an entry at the current value
		table[val] = new HashNode(key, data);		// create a new HashNode with the given key and data and set it as the current entry in the table
		return new DRT(data, "", "");				// return a new DRT to update the data associated with the key
	}
	return table[val]->addnode(key, data);          // if the current entry is not empty, use recursion until able to add a node
}

/*searches the tree for the given key*/
DRT* HashTable::searchnode(string key) {
	int val = hf(key);
	if (!table[val]) return new DRT("", "", "");    // if there isn't an entry at the current value, return a DRT indicating that there is no data associated with the given key
	return table[val]->searchnode(key);				// if there is an entry, use recursion to continue searching for the key
}

/*removes an item from the list*/
DRT* HashTable::remove(string key) { 
	int val = hf(key);											
	if (table[val]) {											
		return table[val]->remove(key, NULL, table[val]);  // if the entry at the current value isn't empty, call HashNode's remove to delete the node
	}
	else return new DRT(key, "", "");                      // if there isn't an entry at the given value, return a new DRT indicating so
}

/*Database search method*/
DRT* HashTable::search(string key) {  
	if (key == "") return new DRT("", "", ""); 	  // checks to see if we're searching on the empty string, if so builds a DRT with first() and last ()
	return searchnode(key);                       // otherwise calls searchnode
}

/*Database modify method*/
DRT* HashTable::modify(string key, string data) { 
	if (key == "") return new DRT("", "", "");
	if (data == "") return remove(key);
	return add(key, data);
}