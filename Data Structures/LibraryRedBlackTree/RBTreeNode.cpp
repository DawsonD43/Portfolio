/*
	Dawson Dauphinais
	CS222, Data Structures
	Date Last Modified: 04/30/2020

	This file contains the methods for manipulating nodes within the RB Tree.
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include "RBTree.h"
#include "RBTreeNode.h"
#include "RBHelper.h"
#include "DRT.h"
using namespace std;

RBTreeNode::RBTreeNode(string key, string data, RBTreeNode* l, RBTreeNode* r, RBTreeNode* p, RBTree* T) { //constructor
	k = key; d = data; left = l; right = r; parent = p; t = T;
	this->setblack(false);
}

RBTreeNode::~RBTreeNode() { //destructor
	delete left;
	delete right;
}

/*similar to search; keeps nsf and psf*/
DRT* RBTreeNode::add(string key, string data, string n, string p) {
	if (k == key) { // check if the key has been found
		DRT* temp = new DRT(d, n, p);
		d = data;   // d is overwritten and becomes the new value of "data'
		string next, prev;
		if (!right) next = n; // if there isn't a right child, next becomes n
		else next = right->first()->getk();   // next becomes the value of the node all the way to the right
		if (!left) prev = p;  // if there isn't a left child, prev becomes p            
		else prev = left->last()->getk();   // prev becomes the value of the node all the way to the left
		return temp;  // modify the DRT using the new value of Data
	}
	if (k < key) { // check to see if the value of k is less than the value of the key we are looking for
		if (right) { // check for a right child
			return right->add(key, data, n, k); // if there's a right child, use recursion to continue searching for the key
		}
		else { // there's no current right child
			right = new RBTreeNode(key, data, NULL, NULL, this, t); // create a new right child
			right->AddProcess();
			return new DRT("", n, k); // return a DRT, keeping track of pfs
		}
	}
	if (left) { // otherwise, check for a left child
		return left->add(key, data, k, p); // if there is a left child, use recursion to continue searching for the desired key
	}
	else {
		left = new RBTreeNode(key, data, NULL, NULL, this, t); // create a new left child if there is no left child
		left->AddProcess();
		return new DRT("", k, p); // return a DRT, keeping track of nsf
	}
}

/*utilizes keeping track of next-so-far and prev-so-far*/
DRT* RBTreeNode::searchnode(string key, string n, string p) {
	if (k == key) { // check if the key has been found
		string next, prev;
		if (!right) next = n; // if there isn't a right child, next becomes n
		else next = right->first()->getk(); // next becomes the value of the node all the way to the right 
		if (!left) prev = p; // if there isn't a left child, prev becomes p
		else prev = left->last()->getk(); // prev becomes the value of the node all the way to the left
		return new DRT(d, next, prev); // return a new DRT with the new values that have been modified
	}
	if (k < key) { // check to see if the value of k is less than the value of the key we are looking for
		if (right) return right->searchnode(key, n, k); // if there is a right child, use recursion to continue searching for the key
		return new DRT("", n, k); //k is now the psf
	}
	if (left) return left->searchnode(key, k, p); // if there is a left child, use recursion to continue searching for the key
	return new DRT("", k, p); // return new DRT keeping track of nsf
}

/*left all the down*/
RBTreeNode* RBTreeNode::first() {
	if (left) return left->first();
	else return this;
}

/*right all the way down*/
RBTreeNode* RBTreeNode::last() {
	if (right) return right->last();
	else return this;
}

string RBTreeNode::getk() { return k; }//get
string RBTreeNode::getd() { return d; } //get
RBTreeNode* RBTreeNode::getright() { return right; } //get
RBTreeNode* RBTreeNode::getleft() { return left; } //get

/*right once, left all the way down (makes use of first ())*/
string RBTreeNode::next() {
	return getright()->first()->getk();
}

/*left once, right all the way down (makes use of last ())*/
string RBTreeNode::prev() {
	return getleft()->last()->getk();
}

DRT* RBTreeNode::remove(string key, string n, string p) {
	//similar to search; keeps track of nsf and psf
	//just works its down to the RBTree to find the node to remove
	//then calls remove ()
	if (k == key) {          // check to see if the key has been found
		string next, prev;
		if (!right) next = n; // if there is no right child, set next equal to n
		else next = right->first()->getk(); // next becomes the value of the node all the way to the right
		if (!left) prev = p;  // if there is no left child, set prev equal to p
		else prev = left->last()->getk(); // prev becomes the value of the node all the way to the left
		DRT* temp = new DRT(this->getd(), next, prev);
		this->remove(); // call remove on the node that matches the key
		return temp; // return a new DRT with modified values
	}
	if (k < key) {  // 
		if (right) return right->remove(key, n, k); // if there is a right child, use recursion to continue searching for the node.
		return new DRT("", n, k); // return a DRT keeping track of psf
	}
	if (left) return left->remove(key, k, p); // if there is a left child, use recursion to continue searching for the node
	return new DRT("", k, p); // return a DRT keeping track of nsf
}
/*deletes the current node*/
void RBTreeNode::remove() { //the physical removal (decides whether it's 0, 1, or 2-child case and possibly copies key and data values and physically removes the deleted node
	RBTreeNode* xd = NULL;
	if (!left && !right) {	   // check if I'm left or right child of parent / 0 child case
		if (parent == NULL) {  // check to see if the node to be removed is the root node
			t->setroot(NULL);  // if it is the root node, set root to NULL
			left = NULL;       // set the left node's pointer to NULL
			right = NULL;      // set the right node's pointer to NULL
			bool callDel = true;
			if (!getcolor(this)) {
				callDel = false;
				delete this;
				return;
			}
			if (callDel) {
				//delete this;
				DelProcess(NULL, parent);
				delete this;
				return;
			}
		}
		else if (parent->getleft() == this) {  // check to see if the node to be deleted is a left child
			parent->setleft(NULL);             // set the left node's parent to NULL
			left = NULL;					   // set the left node's pointer to NULL
			right = NULL;					   // set the right node's pointer to NULL
			bool callDel = true;
			if (!getcolor(this)) {			   // check to see if the color of the node to be deleted is red
				callDel = false;			   // set the flag for calling DelProcess() to false
				delete this;				   // delete the current node
				return;						   // DONE
			}
			if (callDel) { // check the flag to see if the node was red or black
				//delete this;
				DelProcess(NULL, parent); // call DelProcess() if the node was black;
				delete this;
				return;
			}
		}
		else if (parent->getright() == this) { // check to see if the node to be deleted is a right child
			parent->setright(NULL);			   // set the right child's parent to NULL
			left = NULL;					   // set the left node's pointer to NULL
			right = NULL;					   // set the right node's pointer to NULL
			bool callDel = true;
			if (!getcolor(this)) {
				callDel = false;
				delete this;
				return;
			}
			if (callDel) {
				//delete this;
				DelProcess(NULL, parent);
				delete this;
				return;
			}
		}
	}
	else if ((!left && right) || (left && !right)) { // either a left or right child / 1-child case
		if (parent == NULL) {                        // check to see if the node is the root
			if (right) {
				xd = right;
				t->setroot(right);                   // if the root has a right child, set the root to it's right child.
				right->setparent(NULL);              // then set the right child's parent to NULL
			}
			else {
				xd = left;
				t->setroot(left);					 // if the root has a left child, set the root to it's left child,
				left->setparent(NULL);				 // then set the left child's parent to NULL
			}
			left = NULL;                             // set the left node's pointer to NULL
			right = NULL;							 // set the right node's pointer to NULL
			bool callDel = true;
			if (!getcolor(this)) {
				callDel = false;
				delete this;
				return;
			}
			if (callDel) {
				//delete this;
				DelProcess(xd, parent);
				delete this;
				return;
			}
		}
		else if (parent->getleft() == this) { // check to see if the node to be deleted is the left child of its parent node
			if (left) {                       // check to see if the node to be deleted has a left child
				xd = left;
				left->setparent(parent);      // set the left child's parent to the current node's parent
				parent->setleft(left);        // set the parent node's new left child to the left child of the node to be deleted
			}
			else if (right) {                 // check to see if the node to be deleted has a right child
				xd = right;
				right->setparent(parent);     // set the right child's parent to the current node's parent
				parent->setleft(right);       // set the parent node's new left child to the right child of the node to be deleted
			}
			left = NULL;                      // set the left node's pointer to NULL
			right = NULL;                     // set the right node's pointer to NULL
			bool callDel = true;
			if (!getcolor(this)) {
				callDel = false;
				delete this;
				return;
			}
			if (callDel) {
				//delete this;
				DelProcess(xd, parent);
				delete this;
				return;
			}
		}
		else if (parent->getright() == this) { // check to see if the node to be deleted is the right child of its parent node
			if (left) {                        // check to see if the node to be deleted has a left child
				xd = left;
				left->setparent(parent);       // set the left child's parent to the current node's parent
				parent->setright(left);        // set the parent nodes' new right child to the left child of the node to be deleted
			}
			else if (right) {                  // check to see if the node to be deleted has a right child
				xd = right;
				right->setparent(parent);      // set the right child's parent to the current node's parent
				parent->setright(right);       // set the parent node's new right child to the right child of the node to be deleted
			}
			left = NULL;                       // set the left node's pointer to NULL
			right = NULL;                      // set the right node's pointer to NULL
			bool callDel = true;
			if (!getcolor(this)) {
				callDel = false;
				delete this;
				return;
			}
			if (callDel) {
				//delete this;
				DelProcess(xd, parent);
				delete this;
				return;
			}
		}
	}
	else if (left && right) {						// if the node has 2 children
		RBTreeNode* temp = this->getright()->first(); // make a copy of current node and move to the right once, and then left all the way down
		k = temp->getk();							// set the new k value as the k value found from the next node
		d = temp->getd();							// set the new d value as the d value found from the next node
		temp->remove();								// delete the next node
	}
}
void RBTreeNode::setparent(RBTreeNode* p) { parent = p; } //set
void RBTreeNode::setleft(RBTreeNode* l) { left = l; } //set
void RBTreeNode::setright(RBTreeNode* r) { right = r; } //set
RBTreeNode* RBTreeNode::getparent() { return parent; }

bool RBTreeNode::isblack() {
	return black;
}

void RBTreeNode::setblack(bool b) {
	black = b;
}

/*get's direct child of parent*/
RBTreeNode* RBTreeNode::getdirect() {
	if (parent->getright() == this) {
		return right;
	}
	else {
		return left;
	}
}

/*returns true if I am a direct child of parent, false if I am a zigzag child*/
bool RBTreeNode::isdirect() {
	RBTreeNode* p = parent;
	RBTreeNode* gp = parent->getparent();
	if (gp->getright() == p) {
		if (p->getright() == this) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (p->getleft() == this) {
			return true;
		}
		else {
			return false;
		}
	}

}

/*rotate the node into the correct position and recolor accordingly*/
void RBTreeNode::rotate() {
	RBTreeNode* p = parent;
	RBTreeNode* gp = parent->getparent();
	RBTreeNode* z; // zigzag child
	bool temp_color = black; // black
	black = getcolor(parent); // current node node's color is now the same color as the parent node
	parent->setblack(temp_color);
	
	if (parent->getright() == this) { // assign zig-zag child
		z = left;
	}
	else {
		z = right;
	}

	//1
	parent = gp; // x's parent points to gp
	//2
	if (gp) {  // check for grandparent node
		if (gp->getright() == p) {  // if p is a right child of gp, gp's right points to x
			gp->setright(this);
		}
		else if (gp->getleft() == p) { // if p is a left child of gp, gp's left points to x
			gp->setleft(this); 
		}
	}
	else { 
		t->setroot(this); // if gp doesn't exist, the root now points to x
	}

	//3
	p->setparent(this); // p's parent now points to x

	//4
	if (p->getleft() == this) { // if x is a left child of p, x's right points to p
		this->setright(p);
	}
	else if (p->getright() == this) { // if x is a right child of p, x's left points to p
		this->setleft(p);
	}

	//5
	if (p->getleft() == this) { // if x is a left child of p, p's left points to z
		p->setleft(z);
	}
	else if (p->getright() == this) { // if x is a right child of p, p's right points to z
		p->setright(z);
	}

	//6
	if (z) {
		z->setparent(p); // if z exists, z's parent now points to p
	}
}

/*processes rules 3-7 on *this* */
void RBTreeNode::AddProcess() {

	if (this->getparent() == NULL) { // rule 3
		this->setblack(true);
		return; // DONE
	}
	if (getcolor(this->getparent())) { // rule 4
		return; // DONE
	}
	RBTreeNode* gp = parent->getparent();
	RBTreeNode* unc = getsibling(parent, gp);

	if (!getcolor(unc)) { // rule 5
		this->getparent()->setblack(true);
		unc->setblack(true);
		gp->setblack(false);
		gp->AddProcess();
		return;
	}
	if (this->isdirect()) { // rule 6
		parent->rotate();
		return; // DONE
	}
	// rule 7
	this->rotate();   // rotate x up 
	this->rotate();   // rotate x up
	return; // DONE
}
int RBTreeNode::ValidNode() {
	int lc, rc, r;

	if (!black && parent && !parent->isblack()) {
		r = -1;
	}
	else {
		if (left && left->getparent() != this) {
			r = -1;
		}
		else {
			if (left && left->getk() >= k) {
				r = -1;
			}
			else {
				if (right && right->getparent() != this) {
					r = -1;
				}
				else {
					if (right && right->getk() <= k) {
						r = -1;
					}
					else {
						if (left) {
							lc = left->ValidNode();
						}
						else {
							lc = 0;
						}
						if (lc == -1) {
							r = -1;
						}
						else {
							if (right) {
								rc = right->ValidNode();
							}
							else {
								rc = 0;
							}
							if (rc == -1) {
								r = -1;
							}
							else {
								if (lc != rc) {
									r = -1;
								}
								else {
									if (black) {
										r = lc + 1;
									}
									else {
										r = lc;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return r;
}