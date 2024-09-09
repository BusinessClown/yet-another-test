#pragma once
#include <fstream> 
#include <iostream> 
#include <string> 
#include <typeinfo>



using namespace std;


// checks if a certain integer exists in the array and returns the index the integer is in
int isNumPresent(int stored[], int length, int quest) {
	// loops threw array checking for int
	for (int i = 0; i < length; i++) {
		// if it find the integer it returns the index it found it in
		if (stored[i] == quest) {
			return i;
		}
		// if the integer was never found it returns false
		else if (i == length - 1) {
			return false;
		}

	}
}
// changes the stored integer in selected array index 
int modStoredValue(int stored[], int location, string replacment) {
	stored[location] = stoi(replacment);
	return 0;
}

//Adds new inteteger at the end of the array
int storeNewValueAtEnd(int stored[], int location, int newNum) {
	stored[location] = newNum;
	return 0;
}

// removes integer from index
int removesIndex(int stored[], int start, int total ) {
	for (int i = start; i < total; i++) {
		stored[i] = stored[i + 1];
	}
	return 0;
}



// this does the check and if there is a problem throws a problem
void is_digits(string& str) {
	for (char& ch : str) {
		int v = ch; // ASCII Val converted
		if (!(ch >= 48 && ch <= 57)) {

			throw (false);
		}

	}
}

/* this activates a user input and always follows a yes or no text prompt.
If the user enters any thing other than yes or no it prompts the user to try again.
*/
string yesOrNo() {
	string menuYN;
	while (menuYN != "yes" && menuYN != "no") {
		cin >> menuYN;
		if (menuYN == "yes") {
			return "yes";
		}
		else if (menuYN == "no") {
			return "no";
		}
		else {
			cout << "Make sure there are no caps and it is yes or no." << endl;
		}
	}

}

/* 
this is a try catch block that keeps the user from entering an invaled input when only 
the program needs a numarical input. It does not prevent spaces from being inputed as i ran out of 
time.
*/
string check(string& input) {
	try {
		// this does the check and if there is a problem throws a problem
		is_digits(input);

		return "safe";

	}
	catch (bool sOrUs) {
		// Catch invalid_argument exception if input is not a valid integer
		return "unsafe";
	}

}