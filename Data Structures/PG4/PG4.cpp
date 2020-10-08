/*
    Dawson Dauphinais
    CS222, Data Structures
    Date Last Modified: 04/22/2020

    The purpose of this file is to run the program.
        -It also contains the code for the commands used in the program.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include "Tree.h"
#include "DRT.h"
#include "PG4.h"
using namespace std;

/*Create a new Tree and run commands*/
int main(int argc, char** argv) {
    Studs = new Tree();             // set Studs equal to a new Tree
    while (ProcessCommand());       // run the program while ProcessCommand() returns true
    delete Studs;                   // delete the Tree
    return 0;                       
}

/*Checks command given by the user*/
bool ProcessCommand() {

    string cmd;
    getline(cin, cmd); // get the command from the command line
    if (cmd == "EXIT") return false; // exit the program by returning false
    if (cmd == "PRINT") Print();     // call Print()
    else if (cmd == "RPRINT") RPrint(); // call RPrint()
    else if (cmd.substr(0, 3) == "ADD") AddCommand(cmd); // call AddCommand()
    else if (cmd.substr(0, 6) == "REMOVE") RemoveCommand(cmd); // call RemoveCommand()
    else if (cmd.substr(0, 6) == "LOOKUP") LookupCommand(cmd); // call LookupCommand()
    else cout << "Invalid Command!" << endl; // user might have accidentally entered an invalid command, go back to beginning of the function
    return true;
}

/*command that will print the list in forwards order*/
void Print() {

    cout << "Printing list forwards:" << endl;
    DRT* T = Studs->search(""); // search the tree for the empty string
    string k = T->getnext();    // k is now the first entry in the database
    while (k != "") {           // while the list isn't empty, print out all current entries and the number of copies
        delete T;
        T = Studs->search(k);
        cout << "Name:  " << k << "\tCopies:  " << T->getdata() << endl;
        k = T->getnext();
    }
    delete T;                  // delete the DRT to prevent memory leaks
    cout << endl;
}

/*command that will print the list in reverse order*/
void RPrint() {

    cout << "Printing list backwards:" << endl;
    DRT* T = Studs->search("");  // search the tree for the empty
    string k = T->getprev();     // k is now the last entry in the database
    while (k != "") {            // while the list isn't empty, print out all current entries and the number of copies in reverse order
        delete T;
        T = Studs->search(k);    // search for the current entry
        cout << "Name:  " << k << "\tCopies:  " << T->getdata() << endl;
        k = T->getprev();        // set k as the new last value
    }
    delete T;  // delete T to prevent memory leaks
    cout << endl;
}

/*command that will add an entry to the database*/
void AddCommand(string cmd) {

    int q1, q2;
    for (q1 = 0; cmd[q1] != '\"'; q1++);      
    for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);  
    string k = cmd.substr(q1 + 1, q2 - q1 - 1); // k is now the string containing the title that was passed in
    DRT* T = Studs->search(k);                  // T is now the DRT of what searching for the string returned
    if (T->getdata() == "") {                   // check to see if there were any copies/entries already stored in the database
        Studs->modify(k, "1");                  // change the data associated with k to "1"
    }
    else {  // the title/entry must already exist and have at least 1 copy
        string count_copies = to_string(stoi(T->getdata()) + 1); // create a string that contains the number of copies already stored in the database, plus another copy
        Studs->modify(k, count_copies); // change the number of copies associated with k to the new number of copies
    }
    delete T; // delete T to prevent memory leaks

}

/*command that will remove an entry from the database*/
void RemoveCommand(string cmd) {

    int q1, q2;
    for (q1 = 0; cmd[q1] != '\"'; q1++);
    for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
    string k = cmd.substr(q1 + 1, q2 - q1 - 1);
    DRT* T = Studs->search(k); // T is now the DRT of what searching for k returned
    if (T->getdata() == "") // if T's data returns an empty string, there are no current entries in the database
        cout << "\"" << k << "\" does not exist in the library." << endl;

    else {
        if (T->getdata() == "1") { // if there is one copy of the title, call modify to remove a copy
            delete T;
            T = Studs->modify(k, "");
        }
        else { // if there is more than one copy of the title, subtract one from T's data and call modify to change the number of copies
            string d = to_string(stoi(T->getdata()) - 1); 
            delete T;
            T = Studs->modify(k, d);
        }
        cout << "1 copy of \"" << k << "\" has been removed from the library." << endl;
        delete T; // delete T to prevent memory leaks
    }
}

/*command for looking up an entry*/
void LookupCommand(string cmd) {

    string b, e;
    int q1, q2;
    for (q1 = 0; cmd[q1] != '\"'; q1++);
    for (q2 = q1 + 1; cmd[q2] != '\"'; q2++);
    string k = cmd.substr(q1 + 1, q2 - q1 - 1);
    DRT* T = Studs->search(k); // T is now the DRT of what searching for k returned
    if (T->getdata() == "") { // check if there are no current entries
        cout << "\"" << k << "\" does not exist." << endl; 
        if (T->getnext() == "") {        // check to see if the next entry is the end of the list
            e = "the end of the list ";
        }
        else {
            e = T->getnext(); // get the next entry
        }
        if (T->getprev() == "") { // check to see if the previous entry is the beginning of the list
            b = "the beginning of the list ";
        }
        else {
            b = T->getprev(); // get the previous entry
        }
        cout << "\"" << k << "\" would fall between " << b << " and " << e << endl;
        delete T; // delete T to prevent memory leaks
    }
    else {
        cout << "Name:  " << k << "\tCopies:  " << T->getdata() << endl;
        delete T; // delete T to prevent memory leaks
    }
}
