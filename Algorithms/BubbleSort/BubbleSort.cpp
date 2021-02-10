/*
    Dawson Dauphinais
    CS422 - Algorithms
    Date Last Modified: 02/10/2021

    The purpose of this program is to implement Bubble Sort to test its average running time.

    NOTE***: Referenced geeksforgeeks.com for the swap function as well as the bubblesort function

*/
#include <iostream>
#include <stdio.h>
#include "Timer.h"
#include <stdlib.h>
#include <cstdlib>
using namespace std;

/*fills the given array with random numbers*/
void fillArray(int arr[], int s)
{
    for (int i = 0; i < s; i++)
    {
        arr[i] = rand();
    }
}

/*swaps indexes*/
void swap(int* i, int* j)
{
    int tmp = *i;
    *i = *j;
    *j = tmp;
}

/*performs bubble sort*/
void bubbleSort(int arr[], int s)
{
    for (int i = 0; i < s - 1; i++)
    {
        for (int j = 0; j < s - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

/*returns true if the given array is sorted*/
bool isSorted(int arr[], int s)
{
    for (int i = 0; i < s - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return false;
        }
    }
    return true;
}

/*prints the elements contained within the given array*/
void print(int arr[], int s)
{
    for (int i = 0; i < s; i++)
    {
        cout << arr[i] << endl;
    }
}

int main(int argc, char** argv)
{
    Timer timer;
    double avg = 0;
    double time = 0.0;
    int sizes[7] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000 };
    int n;
    for (int j = 0; j < 7; j++) {
        n = sizes[j];
        int* arr = new int[n];
        for (int i = 0; i < 4; i++)
        {
            fillArray(arr, n);
            timer.start();
            bubbleSort(arr, n);
            timer.stop();
            time = timer.getElapsedTimeInMilliSec();
            avg += time;
            cout << "Elapsed Time: " << time << " ms. \n";
            cout << "Sorted: " << std::boolalpha << isSorted(arr, n) << endl;
        }
        avg /= 4.0;
        cout << "AVERAGE TIME FOR INPUT SIZE " << n << ": " << avg << " ms. \n";
        delete [] arr;
    }
    return 0;
}
