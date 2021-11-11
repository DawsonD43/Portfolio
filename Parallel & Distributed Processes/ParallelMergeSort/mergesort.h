/*
 * Author: Dawson Dauphinais
 * ddauphin@nmu.edu
 *
 * CS444 - Parallel & Distributed Processes
 *
 * Parallel Mergesort -- Header file
 *
 * Date Last Modified: 10/31/2021
 *
 * The purpose of this program is to implement Merge Sort in parallel.
 */
#ifndef PG2_MERGESORT_H
#define PG2_MERGESORT_H

#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <string>
#include "mergesort.h"

using namespace std;

struct StringLoc {
    int loc;
    string val;
};

struct ArrData {
    int l;
    int r;
};

struct MergeData {
    string *theArray;
    int currentLoc;
    int l;
    int r;
    string t;
    string *tmp;
    bool isleft;
};

int main(int argc, char **argv);

void fillArr(int sz);

bool isSorted(int sz);

void *binary_search(void *arg);

void *mergesort(void *arg);

void merge(int l, int r);

void *copy(void *arg);

void print(int sz);

#endif //PG2_MERGESORT_H
