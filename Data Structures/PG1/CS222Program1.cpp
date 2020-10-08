// Programmer: Dawson Dauphinais
// CS222: Data Structures
// Date Last Modified: 01/31/2020
//
// The purpose of this program is to allow the user to calculate the cube root of a number using strings. Using strings allows for the user to
// find the cube root of much larger numbers than ints, doubles, or longs, with much greater precision.
//
// CS222Program1.cpp contains all of the methods needed to run the cube root calculator, and also contains a main() method.
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "CS222Program1.h"
using namespace std;

void removeleadingzeroes(string & s) { // removes leading zeroes from a string to insure that leading zeroes don't cause problems when calculating the cube root

	while (s.length() > 1 && s[0] == '0') s = s.substr(1);
}

string add(string a, string b) { // this method adds two strings together and returns the sum as a string

	removeleadingzeroes(a);
	removeleadingzeroes(b);
	while (a.length() < b.length()) a = "0" + a;
	while (b.length() < a.length()) b = "0" + b;
	a = "0" + a;
	b = "0" + b;
	string sum = "";
	int carry = 0;
	for (int i = a.length() - 1; i >= 0; i--) {
		int s = (a[i] - '0') + (b[i] - '0') + carry;
		carry = s / 10;
		sum = ((char)(s % 10 + '0')) + sum;
	}
	removeleadingzeroes(sum);
	return sum;
}

string sub(string a, string b) { // subtracts string b from string a and returns the difference as a string

	removeleadingzeroes(a);
	removeleadingzeroes(b);
	while (b.length() < a.length()) b = "0" + b;
	for (int i = 0; i < b.length(); i++)
		b[i] = 9 - (b[i] - '0') + '0';
	string diff = add(add(a, b), "1").substr(1);
	removeleadingzeroes(diff);
	return diff;
}

string mult(string a, string b) { // allows for multiplication of strings, multiplying string a by string b and returning the product as a string

	removeleadingzeroes(a);
	removeleadingzeroes(b);
	string sum = "0";
	for (int i = 0; i < a.length(); i++)
		for (int j = 0; j < b.length(); j++) {
			string prod = to_string((a[i] - '0') * (b[j] - '0'));
			for (int k = 0; k < a.length() - i - 1 + b.length() - j - 1; k++)
				prod += "0";
			sum = add(sum, prod);
		}
	return sum;
} 

string power(string base, int exponent) { // this allows for the cubeRoot() function to compute the amount of zeroes that need to be added to the number 
											// passed in by the user. The base will always be 10 and the exponent will be 3 times the amount of places specified by the user
	string result="1";
	for (int j = 0; j < exponent; j++) {
		result = mult(result, base);
	}


	return result;
}

bool isLessThanEqualTo(string a, string b) { // method that returns true or false depending on whether string a is less than or equal to string b

	if (a.length() < b.length()) { // if the length of string a is less than the length of string b, a is less than b so return true
		return true;
	}
	else if (a.length() > b.length()) { // if the length of string a is greater than the length of string b, a is larger than b, so return false
		return false;
	}
	else { // if the lengths are equal, subtract to find the difference which will tell us the larger value depending on the sign of the number
		for (int x = 0; x < a.length(); x++) {
			if ((a[x] - '0')<(b[x] - '0')) {
				return true;
			}
			else if ((a[x] - '0') > (b[x] - '0')) {
				return false;
			}
		}
		return true;
	}
}

string cubeRoot(string num, int places) { // cubeRoot actually computes the cube root of a string of numbers to the specified amount of places passed the decimal point

	//num is remainder
	if (num == "0") {
		if (places == 0) {
			return num;
		}
		else {
			num += ".";
			for (int x = 0; x < places; x++) {
				num += "0";
			}
		}
		return num;
	}

	removeleadingzeroes(num);
	int newPlaces = places * 3;
	num = mult(num, power("10", newPlaces));
	string rem = num; // remainder is now the number we are finding the cube root of
	string ans = "0"; // ans starting at 0
	string formula; // declare magic formula for later use
	string tempRes;

	vector<string>eights; //create a vector of length equal to 3 times the remainder
	
	int i = 1; 
	string temp = "1";
	for (temp; isLessThanEqualTo(temp,rem);) { // create 8s table starting at 1, multiplying each previous entry by 8
		eights.push_back(temp);
		temp = mult(temp, "8");
	}
	for (int j = eights.size() - 1; j >= 0; j--) { // go through table of eights backwards starting at last entry (highest value) until there are no entries left
		formula = add( mult( "12", mult(ans, ans) ) , add(mult("6", ans), "1"));
		tempRes = formula;
		tempRes = mult(tempRes, eights[j]); //eights product

		if (isLessThanEqualTo(tempRes, rem)) {
			rem = sub(rem, tempRes);
			ans = add(mult(ans, "2"), "1");
		}
		else if (!isLessThanEqualTo(tempRes, rem)) { //checks to see if the result from the eight-product is less than or equal to the remainder 
			ans = mult(ans, "2"); // double ans if it is not
		}
	}
	return ans.insert(ans.length()-places,"."); // need move decimal to correct position

}

int main(int argc, char** argv) { // main method which calls the cubeRoot function after prompting the user to input the specified information

	string a;
	int b;
	cout << "Please enter a number you'd like to find the cube root of:  ";
	getline(cin, a);
	cout << "Please enter the number of places you would calculate to:  ";
	cin >> b;
	string res = cubeRoot(a, b);
	cout << "The cube root of " << a << " to " << b << " places = " << res << " !" << endl;


}
