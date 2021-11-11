/*
 * Dawson Dauphinais
 * Matrix Multiplication Program -- Headers
 * CS444 - Parallel & Distributed Processes
 *
 * Date Last Modified: 09/14/2021
 *
 */

#ifndef _MATRIXMULT_
#define _MATRIXMULT_

#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <string>

using namespace std;

pthread_t *th;
float **leftMatrix;
float **rightMatrix;
float **resultMatrix;
int MAX;

struct MatrixData {
    int r, c;
};

int main(int argc, char **argv);

void fillMatrix(float **aMatrix, int r, int c);

void createResultMatrix(float **aMatrix, int r, int c);

void *multiply(void *arg);

void deleteMatrix(float **matrix, int row);

void print(float **aMatrix, int r, int c);

#endif