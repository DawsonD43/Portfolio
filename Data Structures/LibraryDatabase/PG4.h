/*
	Dawson Dauphinais
	CS222, Data Structures
	Date Last Modified: 04/22/2020

	This file contains the definitions for PG4.cpp
*/

#ifndef _PG4_
#define _PG4_

#include <string>
#include <cstdlib>
#include "Database.h"
using namespace std;

Database* Studs;

int main(int argc, char** argv);
bool ProcessCommand();
void Print();
void RPrint();
void AddCommand(string cmd);
void RemoveCommand(string cmd);
void LookupCommand(string cmd);

#endif