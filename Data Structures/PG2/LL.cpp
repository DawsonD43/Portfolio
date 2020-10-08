/*
	Dawson Dauphinais
	CS222, Data Structures

	This file contains the methods for manipulating a linked list
*/


#include <iostream>
#include <string>
#include <cstdlib>
#include "LL.h"
#include "LLN.h"
#include "PG2.h"
using namespace std;

LL::LL() { // simple constructor for a Linked List that sets the head to null
	head = NULL;
}

LL::~LL() { // simple destructor for the Linked List that deletes the head of the list
	delete head;
}

void LL::add(string s) { // adds string 's' to the the linked list
	LLN* nn = new LLN(head, s);
	head = nn;
}

void LL::print() { // prints the linked list
	if (head) head->print();
	cout << endl;
	
}

int LL::longest() { // returns the longest string in the linked list as an int
	if (head == NULL) return 0; // if the head is equal to null, the length is zero -> return zero
	return head->longest();
}

/*sorts the list using the radix sorting method*/
void LL::radixsort() {
	cout << "Beginning Sort..." << endl;
	for (int i = head->longest()- 1; i >= 0; i--) {
		LLN** arr = new LLN*[27];
		for (int x = 0; x < 27; x++) { // go through array and initialize each element to null
			arr[x] = NULL;
		}
		head->split(i, arr); //call split on index i in the array of lists
		head = paste2(arr); //set head equal to the new pasted array
		delete[] arr; // delete the array to prevent memory leak
	}
}
