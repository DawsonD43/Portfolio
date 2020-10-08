/*
	Dawson Dauphinais
	CS222, Data Structures
	Date Last Modified: 04/23/2020

	This file contains the main method and runs the program.
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include "HashTable.h"
#include "DRT.h"
#include "PG6.h"
using namespace std;

/*creates a new HashTable and runs the program*/
int main(int argc, char** argv) {
	int size = 100003;
	Studs = new HashTable(size); // Studs is now a new HashTable of size 100003
	while (Process_Command());   // run the program wile ProcessCommand() returns true
	delete Studs;				 // delete the HashTable
	return 0;
}

/*Checks command given by the user*/
bool Process_Command() {
	string cmd;
	getline(cin, cmd);	// get the command from the command line
	if (cmd == "EXIT") return false; // exit the program by returning false
	if (cmd.substr(0, 3) == "ADD") Add_command(cmd); // call AddCommand()
	else if (cmd.substr(0, 6) == "LOOKUP") Lookup_command(cmd); // call LookupCommand()
	else if (cmd.substr(0, 6) == "REMOVE") Remove_command(cmd); // call RemoveCommand()
	else cout << "Invalid command !" << endl; // user might have accidentally entered an incorrect command
	return true;
}

/*add an entry to the database*/
void Add_command(string cmd) {
	int q1, q2;
	for (q1 = 0; cmd[q1] != '\"'; q1++);
	for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
	string k = cmd.substr(q1 + 1, q2 - q1 - 1);  // k is now the string that was passed in
	DRT* T = Studs->search(k);					 // T is now the DRT of what searching for the string returned
	if (T->getdata() == "") {					 // check to see if there any copies/entries already stored in the database
		Studs->modify(k, "1");					 // change the data associated with k to "1"
	}
	else { // the title/entry must already exist and have at least 1 copy
		string count_copies = to_string(stoi(T->getdata()) + 1); // create a string that contains the number of copies already stored in the database, plus another copy
		Studs->modify(k, count_copies); // change the number of copies associated with k to the new number of copies
	}
	cout << "1 copy of \"" << k << "\" has been added to the library." << endl;
	delete T; // delete T to prevent memory leaks
}

/*search for an entry in the database*/
void Lookup_command(string cmd) {
	int q1, q2;
	for (q1 = 0; cmd[q1] != '\"'; q1++);
	for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
	string k = cmd.substr(q1 + 1, q2 - q1 - 1);
	DRT* T = Studs->search(k); // T is now the DRT of what searching for k returned
	if (T->getdata() == "") { // check if there are no current entries
		cout << "\"" << k << " does not exist." << endl;
		delete T;
	}
	else { // print the title and the number of copies
		cout << "Name: " << k << "\tCopies: " << T->getdata() << endl;
		delete T; // delete T to prevent memory leaks
	}


}

/*remove an item from the database*/
void Remove_command(string cmd) {
	int q1, q2;
	for (q1 = 0; cmd[q1] != '\"'; q1++);
	for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
	string k = cmd.substr(q1 + 1, q2 - q1 - 1);
	DRT* T = Studs->search(k); // T is now the DRT of what searching for k returned
	if (T->getdata() == "") { // if T's data returns an empty string, there are no current entries
		cout << "\"" << k << "\" does not exist in the library." << endl;
	}
	else {
		if (T->getdata() == "1") { // if there is one copy, call modify to remove a copy
			delete T;
			T = Studs->modify(k, "");
		}
		else { // if there is more than one copy of the title, subtract 1 from T's data and call modify to change the number of copies
			string d = to_string(stoi(T->getdata()) - 1);
			delete T;
			T = Studs->modify(k, d);
		}
		cout << "1 copy of \"" << k << "\" has been removed from the library." << endl;
		delete T; // delete T to prevent memory leaks
	}
}
