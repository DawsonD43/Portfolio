/*
    Dawson Dauphinais
    CS222, Data Structures

    This file contains the definitions for the LLN class
*/

#ifndef _LLN_
#define _LLN_

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class LLN {

private:

    LLN* next;
    string s;

public:

    /* constructor */
    LLN(LLN* n, string S);

    /* destructor */
    ~LLN();

    /* returns the length of the longest string in the list */
    int longest();

    /* splits the list into 27 lists (stored in array lists) around
       position pos */
    void split(int pos, LLN** lists);

    /* pastes b to the end of the current list */
    void paste(LLN* b);

    /* prints list */
    void print();

    LLN* getNext();

};
#endif