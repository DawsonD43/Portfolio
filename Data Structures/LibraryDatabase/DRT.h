/*
    Dawson Dauphinais
    CS222, Data Structures
    Date Last Modified: 04/22/2020

    This file contains the defintions for the methods found in DRT.cpp
*/
#ifndef _DRT_
#define _DRT_
#include <string>
using namespace std;

class DRT {

private:
    string data;
    string next;
    string prev;

public:

    DRT(string d, string n, string p);
    string getdata();
    string getnext();
    string getprev();

};



#endif

/* DRT.h is the Database Return Type.  It contains three fields:

   The data from the location in the database we're examining.

   The next key field in sequential order after the one we're examining.

   The prev key field in sequential order before the one we're examining.

*/