/*File: util.cpp
* Name: Fonz Hamilton
*/
#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include "util.h"
using namespace std;

int nextWord(string input, int *a, int *b, int *c) {
	int readValue = -1;
	stringstream ss;
	string firstWord;
	string secondWord;

	//*a = NULL;
	//*b = NULL;
	//*c = NULL;

	ss << input;
	ss >> firstWord;	

	if (firstWord.compare("find") == 0) {
		ss >> *a >> *b >> *c;
		if ((*a == ' ' || *a == '\t' || *a == '\n') || (*b == ' ' || *b == '\t' || *b == '\n')) {

			readValue = 1;
		}
		else {
			readValue = 1;
		}
	}
	else if (firstWord.compare("write") == 0) {
		ss >> secondWord;
		if (secondWord.compare("path") == 0) {
			ss >> *a >> *b;
			if ((*a == ' ' || *a == '\t' || *a == '\n')  || (*b == ' ' || *b == '\t' || *b == '\n')) {
                readValue = -1;
               // cout << "enter the correct parameters" << endl;
            }
            else {
				readValue = 2;
				//cout << "Query: write path " << *a << " " << *b << endl;
					
			}
		}
	}

	else if (firstWord.compare("stop") == 0) {
		readValue = 0;
		//cout << "Query: stop" << endl;
	}

	return readValue;
	
}
int nextCommand(int *n, int *f) {
	string input;
	string digit = "";
	string valString = "";
	int number = 0;
	int value = 0;
	int spaceCount = 0;
	bool containsDigit = false;
	bool containsSpaces = false;
	char c;

	while(1) {
		// garbage to make my input stream less bad
		digit = "";
		valString = "";
		containsDigit = false;
		containsSpaces = false;

		stringstream ss;
		std::getline(std::cin, input);
		c = input[0];
		for (unsigned int i = 0; i < input.length(); i++) {
			if (isdigit(input[i])) {
				containsDigit = true;
				if (spaceCount == 1) {
					digit = digit + input[i];
				}
				if (spaceCount == 2) {
					valString = valString + input[i];
				}
				
			}
			if (input[i] == ' ') {
				spaceCount++;
			}
			if (spaceCount == 2) {
				containsSpaces = true;
			}
		
		}
		// I forgot how this works but it does
		if (containsDigit == true) {
			ss << digit << ' ' << valString;
			ss >> number >> value;
		}
		
		//cout << "test for bullshit ass input shit" << endl;
		//cout << "number " << number << endl;
		//cout << "valString " << valString << endl;
		//cout << "value " << value << endl;
		if (c == ' ' || c == '\t' || c == '\n') {
			continue;
		}
		if (c == 'S' || c == 's') {		// stops
			break;
		}
		if ((c == 'C' || c == 'c') && containsDigit == true) {		// call function to heap mod with n
			
			*n = number;
			break;
		}
		if ((c == 'R' || c == 'r') && containsDigit == true) {		// reads HEAPinput.txt
			*f = number;
			break;
		}
		if ((c == 'D' || c == 'd') && containsDigit == true) {
			*f = number;
			break;
		}
		if ((c == 'I' || c == 'i') && containsDigit == true) {
			*n = number;
			break;
		}
		if ((c == 'K' || c == 'k') && containsDigit == true && containsSpaces == true) {
			*n = number;
			*f = value;
			break;
		}
		if (c == 'W' || c == 'w') {		// writes to HEAPout.txt
			break;
		}
		if (c == 'P' || c == 'p') {		// writes the info of the heap pointer
			break;
		}
	}
	
	return c;

}

