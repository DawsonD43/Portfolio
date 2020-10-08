/*
	Dawson Dauphinais
	CS222, Data Structures
	Date Last Modified: 04/02/2020

	This program solves the Towers of Hanoi and prints each move necessary to solve it.

*/

#include <string>
#include <iostream>
#include <cstdlib>
#include "PG3.h"
#include "StackNode.h"
#include "LLStack.h"
using namespace std;

/*prints the moves for solving the puzzle*/
void printMove(int disks, int src, int dest) {
	src += 1; // 1 is added to source and destination for correct output, as the range of src and destination is originally 0-2, whereas it should be 1-3
	dest += 1;
	cout << "Move disk " << disks << " from pole " << src << " to pole " << dest << endl;
}

/*intitalizes each index in the array of stacks, and fill the first pole with the disks*/
void setPoles(LLStack** poles, int disks) {
	int diskVal;
	int i;
	for (int i = 0; i < 3; i++) {
		poles[i] = new LLStack();
	}
	for (i = disks; i >= 1; i--) {
		diskVal = i;
		poles[0]->PUSH(i);
	}
}

/*move disk between source and destination*/
void moveDisk(LLStack** poles, int source, int dest) {

	int top = poles[source]->POP();
	poles[dest]->PUSH(top);
	printMove(top, source, dest);

}

/*Makes the only legal move not involving the 1 disk*/
void evenMove(int disk1Pos, LLStack** poles) {

	int src, dest; //one with smaller disk is src, the other is dest
	int openPole1 = (disk1Pos + 1) % 3; // uses the position of disk 1 to calculate one of the 2 possible open poles
	int openPole2 = (disk1Pos + 2) % 3; // uses the position of disk 1 to calculate one of the 2 possible open poles
	int top1, top2;                     // top1 and top2 will contain the top disks of each of the two poles

	if (poles[openPole1]->ISEMPTY()) { // if the openPole1 is empty, that automatically makes it the destination, and the other pole becomes the source
		dest = openPole1;
		src = openPole2;
		moveDisk(poles, src, dest);
	}
	else if (poles[openPole2]->ISEMPTY()) { // if the openPole2 is empty, that automatically makes it the destination, and the other pole becomes the source
		dest = openPole2;
		src = openPole1;
		moveDisk(poles, src, dest);
	}
	else if (!poles[openPole1]->ISEMPTY() && !poles[openPole2]->ISEMPTY()) { // if neither of the two poles are empty, begin comparisons of top disk on each pole
		top1 = poles[openPole1]->POP(); // top disk of the fist pole
		top2 = poles[openPole2]->POP(); // top disk of the second pole
		if (top1 > top2) {              // if the top disk of the first pole is larger than the top disk of the second pole, move the disk from the second pole onto the first
			poles[openPole1]->PUSH(top1);
			poles[openPole1]->PUSH(top2);
			printMove(top2, openPole2, openPole1);
		}
		else {                         // otherwise move the top disk from the first pole onto the second pole
			poles[openPole2]->PUSH(top2);
			poles[openPole2]->PUSH(top1);
			printMove(top1, openPole1, openPole2);
		}
	}
}

/*takes in the number of disks, and then solves the puzzle based on even or odd moves*/
void Hanoi(int disks, LLStack** poles) {
	cout << endl;
	cout << "Solving......." << endl;
	cout << endl;

	int direction;     // keeps track of which direction disk1 should move
	setPoles(poles, disks); // create the poles
	int totalMoves = pow(2, disks) - 1;
	int disk1Pos = 0; // keeps track of which pole disk 1 is on

	if (disks % 2 == 0) { // if there are an even number of disks, the direction is positive, otherwise the direction is negative
		direction = 1; // right
	}
	else {
		direction = -1; // left
	}

	for (int j = 1; j <= totalMoves; j++) {
		if (j % 2 == 0) { // if it's an even move, call the even move function which performs correct logic for solving
			evenMove(disk1Pos, poles);
		}
		else { // if it's an odd move, move disk 1 in the correct direction to the correct pole
			int origOne = disk1Pos; // used for keeping track of where disk 1 started, so that it correctly prints moves
			disk1Pos += direction; // move the position of disk 1 in the correct direction
			if (disk1Pos == -1) {  // this conditional statement makes sure that disk1Pos is always between 0 and 2
				disk1Pos = 2; 
			}
			else if (disk1Pos == 3) {
				disk1Pos = 0;
			}
			moveDisk(poles, origOne, disk1Pos); // move disk1 to the correct position and print it out
			origOne++;
		}
	}
}

/*main method where the hanoi method is ran. Asks user for the number of disks*/
int main(int argc, char** argv) {
	int disks;
	cout << "Enter the Number of Disks: " << endl;
	cin >> disks;
	LLStack* poles[3]; // creates the array of 3 stacks
	Hanoi(disks, poles);
	return 0;
	delete[] poles; // delete the array of pointers to prevent memory leaks
}