/*
	Dawson Dauphinais
	CS222, Data Structures
	Date Last Modified: 02/27/2020

	This file contains the definitions for the LLStack class.
*/

#ifndef _LLSTACK_
#define _LLSTACK_

#include <iostream>
#include <string>
#include <cstdlib>
#include "StackNode.h"
using namespace std;

class StackNode;
class LLStack {
private:
	StackNode* head;
public:

	/*stack constructor*/
	LLStack();

	/*simple stack destructor*/
	~LLStack();

	/*pushes a string onto the stack*/
	void PUSH(int s);

	/*return the element at the top of the stack*/
	int POP();

	/*returns true if stack is empty*/
	bool ISEMPTY();
};


#endif