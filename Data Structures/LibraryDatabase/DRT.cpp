/*
    Dawson Dauphinais
    CS222, Data Structures
    Date Last Modified: 04/22/2020

    This file creates the DRT return type.
*/
#include <string>
#include "DRT.h"
using namespace std;

DRT::DRT(string d, string n, string p) {

    data = d; next = n; prev = p;
}

string DRT::getdata() { return data; }

string DRT::getnext() { return next; }

string DRT::getprev() { return prev; }