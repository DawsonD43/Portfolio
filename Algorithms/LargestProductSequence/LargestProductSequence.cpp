/*
 * Author: Dawson Dauphinais
 * Date Last Modified: 03/19/2021
 *
 * The purpose of this program is to use Dynamic Programming to find the largest product of a given sequence.
 * 
 * Input: A sequence of numbers.
 * Output: The maximum product obtained from the sequence.
 * Time Complexity: T(n) = O(n).
 *
 * Future Releases:
 *		- Should allow user to input a sequence of numbers.
 *		- Give the sequence that produced the largest product.
 */

#include <iostream>
#include <vector>
using namespace std;

int largestSum(vector<int> arr)
{
	int max = 0;
	auto n = arr.size();
	vector<int> T;
	T.push_back(arr[0]);
	for (auto i = 1; i < n; i++)
	{
		T.push_back(T[i - 1] * arr[i]);
		if (max < T[i])
		{
			max = T[i];
		}
	}
	return max;
}

int main()
{
	vector<int> arr = {2, 3, -1, -2, 3, 5, -2, 2};
	int x = largestSum(arr);
	cout << "MAX: " << x << endl;
	return 0;
}
