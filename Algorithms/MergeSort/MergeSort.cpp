/*
	Dawson Dauphinais
	CS422 - Algorithms
	Date Last Modified: 02/10/2021

	The purpose of this program is to implement MergeSort to test its average running time.

	NOTE***: The merge function was referenced from geeksforgeeks.com

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

/*merges the arrays back together*/
void merge(int arr[], int l, int m, int r)
{
	int s1 = m - l + 1;
	int s2 = r - m;
	int* A = new int[s1];
	int* B = new int[s2];

	for (int i = 0; i < s1; i++)
		A[i] = arr[l + i];
	for (int j = 0; j < s2; j++)
		B[j] = arr[m + 1 + j];

	int i = 0;
	int j = 0;
	int k = l;

	while (i < s1 && j < s2)
	{
		if (A[i] <= B[j])
		{
			arr[k] = A[i];
			i++;
		}
		else
		{
			arr[k] = B[j];
			j++;
		}
		k++;
	}
	while (i < s1)
	{
		arr[k] = A[i];
		i++;
		k++;
	}
	while (j < s2)
	{
		arr[k] = B[j];
		j++;
		k++;
	}
	delete[]A;
	delete[]B;
}

/*performs mergesort*/
void mergeSort(int* arr, int l, int r)
{
	if (l >= r)
	{
		return; //returns recursively
	}
	int m = l + (r - l) / 2;
	mergeSort(arr, l, m);
	mergeSort(arr, m + 1, r);
	merge(arr, l, m, r);
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

int main(int argc, char* argv)
{
	double time = 0.0;
	double AVERAGE = 0;
	Timer timer;
	int sizes[7] = { 1000, 2000, 4000, 8000, 16000, 32000, 64000 };
	int n;
	for (int i = 0; i < 7; i++) {
		n = sizes[i];
		int* arr = new int[n];
		for (int j = 0; j < 4; j++)
		{
			fillArray(arr, n);
			timer.start();
			mergeSort(arr, 0, n - 1);
			timer.stop();
			time = timer.getElapsedTimeInMicroSec();
			AVERAGE += time;
			cout << "Elapsed Time: " << time << " ms. \n";
			cout << "Sorted: " << std::boolalpha << isSorted(arr, n) << endl;
		}
		AVERAGE /= 4.0;
		cout << "AVERAGE TIME FOR INPUT SIZE " << n << ": " << AVERAGE << " microsec. \n";
		delete[] arr;
	}
	return 0;
}
