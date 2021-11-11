/*
    Author: Dawson Dauphinais
    Course: CS444 - Parallel & Distributed Processes
    Date Last Modified: 09/14/2021

    The purpose of this program is to multiply two matrices together using multiple threads.
*/

#include <iostream>
#include <pthread.h>
#include <string>
#include "matrixmult.h"

using namespace std;

int m, n, p;

/*A simple struct that holds row and column data*/

/*fills a 2D array with values from the command line.*/
void fillMatrix(float **aMatrix, int r, int c) {
    for (int i = 0; i < r; i++) {
        aMatrix[i] = new float[c];
        for (int j = 0; j < c; j++) {
            cin >> aMatrix[i][j];
        }
    }
}

/*allocates memory for the resultant matrix*/
void createResultMatrix(float **aMatrix, int r, int c) {
    for (int i = 0; i < r; i++) {
        aMatrix[i] = new float[c];
    }
}

/*multiplies two matrices*/
void *multiply(void *x) {
    auto *pos = (struct MatrixData *) x; // retrieve the struct's data
    for (int i = 0; i < n; i++) {
        resultMatrix[pos->r][pos->c] += leftMatrix[pos->r][i] *
                                        rightMatrix[i][pos->c]; // calculate the value based on what thread is doing the current work
    }
    return nullptr;
}

/*prints the values in the matrix-- in matrix form*/
void print(float **aMatrix, int r, int c) {
    cout << endl;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cout << aMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

/*Deallocates an array of pointers, as dynamic 2D arrays cannot simply be deleted*/
void deleteMatrix(float **matrix, int row) {
    for (int i = 0; i < row; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main(int argc, char **argv) {

    cin >> m;
    cin >> n;
    cin >> p;

    MAX = m * p;

    leftMatrix = new float *[m];        //
    rightMatrix = new float *[n];       // create three matrices that will contain float values
    resultMatrix = new float *[MAX];    //

    fillMatrix(leftMatrix, m, n);            // fills the first matrix with float values based on user input
    fillMatrix(rightMatrix, n, p);           // fills the second matrix with float values based on user input
    createResultMatrix(resultMatrix, m, p);  // allocates memory for the resulting matrix of size m*p

    th = new pthread_t[MAX];                 // create the array of threads of size m*p
    struct MatrixData data[MAX];             // create an array of MatrixData structs
    int i = 0;
    for (int j = 0; j < m; j++) {
        for (int k = 0; k < p; k++) {
            data[i].r = j;                   // set the row value for the current struct
            data[i].c = k;                   // set the column value for the current struct
            pthread_create(&th[i], nullptr, multiply,
                           &data[i]);        // create the thread and pass the position that the thread should work with
            i++;
        }
    }
    for (int j = 0; j < MAX; j++) {
        pthread_join(th[j], nullptr);   // wait for the threads to finish !
    }

    print(resultMatrix, m, p);                     // prints the results

    deleteMatrix(resultMatrix, m);                 //
    deleteMatrix(leftMatrix, m);                   // delete the three matricies to avoid memory leaks
    deleteMatrix(rightMatrix, n);                  //

    delete[] th;                                   // delete the thread array
}