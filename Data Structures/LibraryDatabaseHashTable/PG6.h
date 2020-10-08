/*
	Dawson Dauphinais
	CS222, Data Structures
	Date Last Modified: 04/23/2020

	This file contains the definitions of the functions found in PG6.cpp
*/
#ifndef _PG6_
#define _PG6_

#include <string>
#include <cstdlib>
#include "Database.h"
using namespace std;

Database* Studs;

int main(int argc, char** argv);
bool Process_Command();
void Add_command(string cmd);
void Remove_command(string cmd);
void Lookup_command(string cmd);

#endif