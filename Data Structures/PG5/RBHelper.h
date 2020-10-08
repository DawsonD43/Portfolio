/*
	Dawson Dauphinais
	CS222, Data Structures
	Date Last Modified: 04/28/2020

	This file contains the definitions of the functions found in the RBHelper.cpp file.
*/
#ifndef _RBHELPER_
#define _RBHELPER_

#include <iostream>
#include <string>
#include <cstdlib>
#include "RBTreeNode.h"
using namespace std;

bool getcolor(RBTreeNode* n);
RBTreeNode* getsibling(RBTreeNode* n, RBTreeNode* p);
void DelProcess(RBTreeNode* x, RBTreeNode* p);

#endif