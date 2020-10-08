/*
	Dawson Dauphinais
	CS222, Data Structures
	Date Last Modified: 04/23/2020

	This file allows for the DRT to act as a return type that returns more than one item.
*/

#include <string>
#include "DRT.h"
using namespace std;

/*constructor that allows more than one return*/
DRT::DRT (string d, string n, string p) {

	data = d; next = n; prev = p;
}

string DRT::getdata() { return data; } 

string DRT::getnext() { return next; }

string DRT::getprev() { return prev; }