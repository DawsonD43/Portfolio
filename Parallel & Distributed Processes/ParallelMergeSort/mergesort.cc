/*
 * Author: Dawson Dauphinais
 * ddauphin@nmu.edu
 *
 * CS444 - Parallel & Distributed Processes
 *
 * Parallel Mergesort pt. 2
 *
 * Date Last Modified: 11/01/2021
 *
 * The purpose of this program is to implement Merge Sort in parallel.
 *
 */
#include <iostream>
#include <pthread.h>
#include <string>
#include "mergesort.h"

using namespace std;

int n;
string *arr;

/*fills array of size n with user input*/
void fillArr(int sz) {
    for (int i = 0; i < sz; i++) {
        cin >> arr[i];
    }
}

/*prints out the contents of the array*/
void print(int sz) {
    cout << endl;
    for (int i = 0; i < sz; i++) {
        cout << arr[i] << endl;
    }
}

/*returns true if the main array is sorted*/
bool isSorted(int sz) {
    for (int i = 0; i < sz; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

/*places the string into the correct position in the main array.*/
void *copy(void *arg) {
    auto *stringLoc = (StringLoc *) arg;
    int pos = stringLoc->loc;
    string value = stringLoc->val;
    arr[pos] = value;
    return nullptr;
}

/*splits the array recursively*/
void *mergesort(void *arg) {
    auto *index = (ArrData *) arg;
    int low = index->l;
    int high = index->r;
    int mid = low + (high - low) / 2;
    ArrData d1 = {low, mid};                                      // d1 is a struct that will contain the low and mid-position so the thread knows where to work
    ArrData d2 = {mid + 1, high};                              // d1 is a struct that will contain the mid-position + 1 and the high position so the thread knows where to work
    pthread_t left, right;                                        // two threads, one for the left side and one for the ride side
    if (low < high) {
        pthread_create(&left, nullptr, mergesort, &d1);        // create the thread to sort the left side of the array, and give it the data for the first half
        pthread_join(left, nullptr);                    // wait for the left thread to finish
        pthread_create(&right, nullptr, mergesort, &d2);       // create the thread to sort the right side of the array, and give it the data for the second half
        pthread_join(right, nullptr);                   // wait for the right thread to finish
        merge(low, high);                                         // merge the arrays
    }
    return nullptr;
}

/*performs a variation of binary search to figure out where the string should be placed in the array*/
void *binary_search(void *arg) {
    auto *d = (MergeData *) arg;
    string *tempArr = d->theArray;
    int pos = d->currentLoc;
    int fst = d->l;
    int lst = d->r;
    string target = d->t;
    string *temp = d->tmp;
    bool left = d->isleft;
    int mid;

    /*logic for the actual search*/
    while (fst <= lst) {
        mid = (fst + lst) / 2;
        if ((target == temp[mid] && left) || (target < temp[mid])) {
            lst = mid - 1;
        } else {
            fst = mid + 1;
        }
    }

    int loc = pos + fst;   // calculate the position that the value should be inserted
    tempArr[loc] = target; // insert the value into its corresponding position in the tempArr
    return nullptr;
}


/*merges the array back together*/
void merge(int left, int right) {
    string *A, *B;
    int mid = (left + right) / 2;

    //two temporary arrays; one that will hold the values of the left side of the array,
    //and one that will hold the values on the right
    A = &arr[left];
    B = &arr[mid + 1];

    //sizes of the corresponding arrays
    int size = right - left + 1;
    int szA = mid - left + 1;
    int szB = size - szA;

    //create two arrays of the MergeData structs, one for the left
    //side and one for the right side of the array
    MergeData d[szA];
    MergeData d2[szB];

    //create two arrays of threads; one for the amount of values on the
    //left side of the array, and one for amount of values on the right
    pthread_t thA[szA];
    pthread_t thB[szB];

    //create a temporary array of the actual size
    auto *tempArr = new string[size];

    // variables that will be used for keeping track of different positions
    int posA = 0, posB = 0, arrCount = 0;

    //loop through the left side and add a MergeData struct to the corresponding array
    for (int i = left; i <= mid; i++) {
        d[arrCount] = {tempArr, posA, 0, szB - 1, arr[i], B, true};
        arrCount++;
        posA++;
    }

    arrCount = 0;

    //loop through the right side and add a MergeData struct to the corresponding array
    for (int j = mid + 1; j <= right; j++) {
        d2[arrCount] = {tempArr, posB, 0, szA - 1, arr[j], A, false};
        arrCount++;
        posB++;
    }

    //create threads to search the left side of the array
    for (int i = 0; i < szA; i++) {
        pthread_create(&thA[i], nullptr, binary_search, &d[i]);
    }

    //create threads to search the right side of the array
    for (int j = 0; j < szB; j++) {
        pthread_create(&thB[j], nullptr, binary_search, &d2[j]);
    }

    // reset the values of the counters to zero
    posA = 0;
    posB = 0;

    // On the left side of the array, calculate the position that the current value should be placed
    for (int x = left; x <= mid; x++) {
        pthread_join(thA[posA], nullptr);
        posA++;
    }

    // On the right side of the array, calculate the position that the current value should be placed
    for (int y = mid + 1; y <= right; y++) {
        pthread_join(thB[posB], nullptr);
        posB++;
    }

    // reset the counter for the array back to zero
    arrCount = 0;

    // Copy the temp array back into the original array using a parallel copy
    for (int i = left; i <= right; i++) {
        StringLoc stringLoc = {i, tempArr[arrCount]};
        pthread_t cpy;
        pthread_create(&cpy, nullptr, copy, &stringLoc);
        pthread_join(cpy, nullptr);
        arrCount++;
    }
}

int main(int argc, char **argv) {
    cin >> n;                                               // get the size of the array from the user
    arr = new string[n];                                    // allocate space for the array
    fillArr(n);                                             // fill the array with user input
    ArrData data{0, n - 1};                            // this struct allows the beginning and end position of the array
    pthread_t th;                                           //
    pthread_create(&th, nullptr, mergesort, &data);     // create a thread and have it run the mergesort function on the array with the data from the struct
    pthread_join(th, nullptr);                   // wait for the thread to finish
    print(n);                                               // print out the contents of the sorted array
    delete[] arr;                                           // delete the array of strings to prevent any memory leaks
    return 0;
}
