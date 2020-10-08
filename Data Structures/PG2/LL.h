/*
    Dawson Dauphinais
    CS222, Data Structures

    This file contains the defintions used in the LL class
*/
#ifndef _LL_
#define _LL_

#include <iostream>
#include <string>
#include <cstdlib>
#include "LLN.h"
using namespace std;

class LLN;

class LL {

private:
    LLN* head;

public:

    /* constructor */
    LL();

    /* destructor */
    ~LL();

    /* adds a string to the head of the linked list */
    void add(string S);

    /* runs the radixsort.  Uses a loop to run split/paste for each
       character position.  */
    void radixsort();

    /* prints out the linked list */
    void print();

    int longest(); 
};


#endif