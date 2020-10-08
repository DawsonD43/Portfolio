/*
	Dawson Dauphinais
	CS222, Data Structures
	Date Last Modified: 04/28/2020
	
	This file contains helper methods that allow for easier access of certain information.

	This file also contains the logic for deleting nodes.
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include "RBTreeNode.h"
#include "RBHelper.h"
#include "RBTree.h"
using namespace std;

/*return black if n is NULL, otherwise returns the color of n*/
bool getcolor(RBTreeNode* n) {
	if (n == NULL) {
		return true;
	}
	return n->isblack();
}

/*returns the child of p that isn't n*/
RBTreeNode* getsibling(RBTreeNode* n, RBTreeNode* p) {
	if (p->getright() == n) {
		if (p->getleft()) {
			return p->getleft();
		}
		else {
			return NULL;
		}
	}
	else if (p->getleft() == n) {
		if (p->getright()) {
			return p->getright();
		}
		else {
			return NULL;
		}
	}
	else {
		return NULL;
	}
}

/*processes rules 4-10 on x and p*/
void DelProcess(RBTreeNode* x, RBTreeNode* p) {
	// if the rules say to RESTART, you can recursively call this method on the appropriate values of x and p
	RBTreeNode* z;
	if (!getcolor(x)) { // rule 4
		//cout << "Trying Rule 4" << endl;
		x->setblack(true);
		return;
	}
	if (!p) { // rule 5
		//cout << "Trying Rule 5" << endl;
		return;
	}
	RBTreeNode* w;
	//cout << "Trying Rule 6" << endl;
	w = getsibling(x, p); // rule 6
	if (!getcolor(w)) { // rule 7
		//rotate w up once
		// restart
		//cout << "Trying Rule 7 " << endl;
		w->rotate();
		DelProcess(x, p);
		return;
	}
	if (getcolor(w->getleft()) && getcolor(w->getright())) { // rule 8
		//cout << "Trying Rule 8" << endl;
		w->setblack(false);
		x = p;
		p = p->getparent();
		DelProcess(x, p);
		return;
	}
	if (!getcolor(w->getdirect())) { // rule 9
		//cout << "Trying Rule 9" << endl;
		w->getdirect()->setblack(true); 
		w->rotate();
		return;
	}

	//cout << "Trying Rule 10" << endl;
	//rotate w's zigzag child up twice, recolor w black, DONE!
	if (w->getparent()->getright() == w) {
		z = getsibling(w->getright(), w);
	}
	else {
		z = getsibling(w->getleft(), w);
	}
	z->rotate();
	z->rotate();
	w->setblack(true);
	return;
}