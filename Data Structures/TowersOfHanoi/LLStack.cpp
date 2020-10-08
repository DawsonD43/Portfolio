/*
	Dawson Dauphinais
	CS222, Data Structures
	Date Last Modified: 02/27/2020

	This file contains the methods used by the LLStack Class.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include "StackNode.h"
#include "LLStack.h"
using namespace std;

/*constructor for stack, sets head to null*/
LLStack::LLStack() {

	head = NULL;
}

/*simple stack destructor*/
LLStack::~LLStack() {

	delete head;
}

/*pushes string onto stack*/
void LLStack::PUSH(int s) {
	head = new StackNode(s, head);
}

/*returns the element from the top of the stack */
int LLStack::POP() {

	StackNode* h = head;
	head = h->getnext();
	h->setnext(NULL);
	int s = h->getS();
	delete h;
	return s;
}
/*returns true if the stack is empty*/
bool LLStack::ISEMPTY() {

	return !head;
}

