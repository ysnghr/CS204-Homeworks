/*-------------------------------------------------------

Faculty of Engineering and Natural Sciences
CS204 Advanced Programming
Spring 2021
Homework 3 – Display All Ordered Subsequences with a Hybrid Linked List Structure
Task: implement a program that stores and displays all ordered subsequences of some input integers

Input: integers

Output: printing all subsequences of these integers

Author: Yasin Ughur

Date: 3/23/2021

---------------------------------------------------------*/

#include <iostream>
#include <sstream>
#include "Yasinughur_Ughur_Yasin_hw3_subSequence.h"

using namespace std;

// Gets numbers as string from user
string getNumbers()
{
	cout << "Please enter the numbers in a line: ";
	string line;
	getline(cin, line);
	cout << endl;
	return line;
}

// with stringstream checks the line is empty or not
bool checkLineIsEmpty(string text)
{
	istringstream stream(text);
	int i = 0;
	while(stream >> text)
	{
		i += 1;
	}
	//if it is zero returns false, otherwise true
	return (i == 0) ? false : true;
}


int main()
{
	string numbers = getNumbers();

	if (checkLineIsEmpty(numbers))
	{
		istringstream stream(numbers);
		int eachNum;
		SubSeqsList myClass;
		
		while (stream >> eachNum)
		{
			// checking the sign of the number 
			// if it is negative we need to delete otherwise we need to add it to our subseqheadnode linkedlist
			if (eachNum >= 0)
			{
				if (myClass.checkExists(eachNum) == false)
				{
					myClass.insertSubSeqs(eachNum);
				}
			}
			else
			{
				myClass.deleteSubSeqs(eachNum);
			}
		}
		myClass.displayStructure();
		myClass.deleteAll();
	}
	else
		// if the line is empty the program prints message and then stops
	{
		cout << "FINAL CONTENT" << endl;		cout << "List is empty!" << endl;
	}
}