/*
	Dawson Dauphinais
	CS222, Data Structures
	Date Last Modified: 04/02/2020

	This file contains the definitions for the PG3.cpp file (main program).
*/

#ifndef _PG3_
#define _PG3_

#include <string>
#include <iostream>
#include <cstdlib>
#include "LLStack.h"
#include "StackNode.h"
using namespace std;

/*main method where the hanoi method is ran. Asks user for the number of disks*/
int main(int argc, char** argv);

/*takes in the number of disks, and then solves the puzzle based on even or odd moves*/
void Hanoi(int disks, LLStack** poles);

/*intitalizes each index in the array of stacks, and fill the first pole with the disks*/
void setPoles(LLStack** poles, int disks);

/*prints moves necessary to solve puzzle*/
void printMove(int disks, int src, int dest);

/*makes the only legal move not involving disk 1*/
void evenMove(int disk1Pos, LLStack** poles);

/*performs necessary move(s) on pole*/
void moveDisk(LLStack** poles, int src, int dest);
#endif
