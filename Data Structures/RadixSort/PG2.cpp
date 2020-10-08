/*
Dawson Dauphinais
CS222, Data Structures
Date Last Modified: 02/20/2020

The purpose of this program is to create a Radix sort using recursion on linked lists

*/

#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include"PG2.h"
#include"LL.h"
#include "LLN.h"
using namespace std;

LLN* paste2(LLN** lists){ // pastes the lists in the array of lists back together and then returns the head of the paste list
	LLN* list = NULL; //create a new list that will contain the pasted lists
	for (int i = 0; i < 27; i++) { 
		if (lists[i] != NULL) {
			if (list == NULL) {
				list = lists[i];
			}
			else {
				list->paste(lists[i]);
			}
		} 
	}
	return list; // return the list pasted back together
}

int main(int argc, char** argv) { // run the program to ask the user for strings until they enter an empty line and then sort the list using radixsort

	LL* List = new LL();
	string userStr;
	
	while (true) {
		cout << "Enter a string: " << endl;
		getline(cin, userStr);
		if (!userStr.empty()) {
			List->add(userStr);
		}
		else {
			List->radixsort();
			List->print();
			break;
		}
	}
	delete List; // delete the linked list to prevent memory leaks
	return 0;
}