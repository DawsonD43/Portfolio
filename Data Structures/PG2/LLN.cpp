/*
    Dawson Dauphinais
    CS222, Data Structures
    This file contains the code for the methods involving the linked list nodes
*/


#include<iostream>
#include<string>
#include<cstdlib>
#include"LLN.h"
using namespace std;

/* constructor */
LLN::LLN(LLN* n, string str) { 
    s = str;
    next = n;
}

/* destructor */
LLN::~LLN() {
    delete next;
}

/* returns the length of the longest string in the list */
int LLN::longest() {
    int max;
    if (next) max = next->longest(); // if there's a next, call longest on next and set equal to max
    else return s.length();

    if (s.length() < max) { // if the length of the string is less than the current max, return max
        return max;
    }
    else { // otherwise return the length of the string
        return s.length();
    }
}

/* splits the list into 27 lists (stored in array lists) around
   position pos */
void LLN::split(int pos, LLN** lists) {
   
    if (next) next->split(pos, lists);
    if (pos >= s.length()) {
        next = lists[0];
        lists[0] = this;
    }
    else {
        int p = (s[pos] - 'A')+1;
        next = lists[p];
        lists[p] = this;
    }
}

/* pastes b to the end of the current list */
void LLN::paste(LLN* b) {
    if (!next) next = b;
    else next->paste(b);
}

/* get the next node in the list */
LLN* LLN::getNext() {
    return next;
}

/* prints list */
void LLN::print(){
    cout << s << endl;
    if (next) next->print();
}
