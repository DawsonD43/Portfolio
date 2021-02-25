/*
 * Author: Dawson Dauphinais
 * CS422 - Algorithms
 * Date Last Modified: 02/17/2021
 *
 * This program implements the grade-school algorithm for multiplying as well as Karatsuba's Algorithm for multiplying two large numbers,
 * and then compares the two results.
 *
 * The program uses strings rather than long long data types so that the values can be much larger.
 */
#include<iostream>
#include<string>
#include<cmath>
#include "Timer.h"
using namespace std;

/*removes leading zeroes from string s*/
void remove_leading_zeroes(string& s)
{
	while (s.length() > 1 && s[0] == '0') s = s.substr(1);
}

/*finds the shorter string and prepends 0's to the front. does nothing if the strings are equal length*/
void add_leading_zeroes(string& a, string& b)
{
	const int a_len = a.length();
	const int b_len = b.length();
	int zeros;
	if (a_len > b_len)
	{
		zeros = a_len - b_len;
		for (int i = 0; i < zeros; i++)
		{
			b.insert(0, "0");
		}
	}
	else if (a_len < b_len)
	{
		zeros = b_len - a_len;
		for (int i = 0; i < zeros; i++)
		{
			a.insert(0, "0");
		}
	}
}

/*adds a 0 to make the string even*/
void make_even(string& s)
{
	s.insert(0, "0");
}

/*adds two numbers together as strings*/
string add(string a, string b)
{
	remove_leading_zeroes(a);
	remove_leading_zeroes(b);
	while (a.length() < b.length())
	{
		a = "0" + a;
	}
	while (b.length() < a.length())
	{
		b = "0" + b;
	}
	a = "0" + a;
	b = "0" + b;
	string sum = "";
	int carry = 0;
	for (int i = a.length() - 1; i >= 0; i--)
	{
		int s = (a[i] - '0') + (b[i] - '0') + carry;
		carry = s / 10;
		sum = ((char)(s % 10 + '0')) + sum;
	}
	remove_leading_zeroes(sum);
	return sum;
}

/*multiplies two numbers as strings... GRADE-SCHOOL ALGORITHM*/
string multiply(string a, string b)
{
	remove_leading_zeroes(a);
	remove_leading_zeroes(b);
	string total = "0";
	for (int i = 0; i < a.length(); i++)
	{
		for (int j = 0; j < b.length(); j++)
		{
			string product = to_string((a[i] - '0') * (b[j] - '0'));
			for (int k = 0; k < a.length() - i - 1 + b.length() - j - 1; k++)
			{
				product += "0";
			}
			total = add(total, product);
		}
	}
	return total;
}

/*subtracts two numbers as strings*/
string subtract(string a, string b)
{
	while (b.length() < a.length()) b = "0" + b;
	for (int i = 0; i < b.length(); i++)
		b[i] = 9 - (b[i] - '0') + '0';
	string diff = add(add(a, b), "1").substr(1);
	remove_leading_zeroes(diff);
	return diff;
}

/*multiplies two strings using Karatsuba's Algorithm*/
string karatsuba(string a, string b)
{
	add_leading_zeroes(a, b);
	if (a.length() % 2 != 0) make_even(a);
	if (b.length() % 2 != 0) make_even(b);
	int n = (int)fmax(a.length(), b.length());
	
	if (n < 6)
	{
		long long x = stoll(a);
		long long y = stoll(b);
		return to_string(x * y);
	}
	
	string xh = a.substr(0, n / 2);
	string xl = a.substr(n / 2, n - n / 2);
	string yh = b.substr(0, n / 2);
	string yl = b.substr(n / 2, n - n / 2);
	
	string A = karatsuba(xh, yh); //A
	string B = karatsuba(xl, yl); //B
	string C = karatsuba(add(xh, xl), add(yh, yl)); //C
	string D = subtract(C, add(A, B));
	
	for (int i = 0; i < 2 * (n - n / 2); i++) A.append("0"); // A*(10^n)
	for (int i = 0; i < n - n / 2; i++) D.append("0"); // B*(10^n/2)
	string xy = add(add(A, B), D);
	remove_leading_zeroes(xy);
	return xy;
}

int main(int argc, char** argv)
{
	string a, b;
	cout << "Enter the first value: " << endl;
	cin >> a;
	cout << "Enter the second value: " << endl;
	cin >> b;
	
	Timer t1, t2;
	double time = 0.0;
	
	t1.start();
	string K = karatsuba(a, b);
	t1.stop();
	time = t1.getElapsedTimeInMilliSec();
	cout << endl;
	cout << "KARATSUBA'S ALGORITHM: " << K << " took: " << time << " ms. \n";
	
	t2.start();
	string G = multiply(a, b);
	t2.stop();
	time = t2.getElapsedTimeInMilliSec();
	cout << endl;
	cout << "GRADE-SCHOOL ALGORITHM: " << G << " took: " << time << " ms. \n";
	
	return 0;
}