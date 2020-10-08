/*
	Dawson Dauphinais
	CS222, Data Structures
	Date Last Modified: 02/27/2020

	This file contains the methods used by the StackNode class.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include "StackNode.h"
using namespace std;

/*stack node constructor*/
StackNode::StackNode(int s, StackNode* n) {
	S = s;
	next = n;
}

/*simple destructor*/
StackNode::~StackNode() {
	delete next;
}

/*gets int and returns it*/
int StackNode::getS() {
	return S;
}

/*gets the next node in the stack and return in*/
StackNode* StackNode::getnext() {
	return next;
}

/*set the next node*/
void StackNode::setnext(StackNode* n) {
	next = n;
}