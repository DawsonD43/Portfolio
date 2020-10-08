/*
	Dawson Dauphinais
	CS222, Data Structures
	Date Last Modified: 02/27/2020

	This file contains the definitions for the StackNode class.
*/

#ifndef _STACKNODE_
#define _STACKNODE_

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class StackNode {
private:
	int S;
	StackNode* next;
public:
	/*Stack Node constructor, takes in a string and a Stack Node*/
	StackNode(int s, StackNode* n);

	/*simple stack node destructor*/
	~StackNode();

	/*gets the current int*/
	int getS();

	/*returns the next stack node*/
	StackNode* getnext();

	/*sets the next node*/
	void setnext(StackNode* n);
};

#endif

