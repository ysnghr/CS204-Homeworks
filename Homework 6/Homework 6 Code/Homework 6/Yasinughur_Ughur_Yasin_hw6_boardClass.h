#ifndef Yasinughur_Ughur_Yasin_hw6_boardClass_h
#define Yasinughur_Ughur_Yasin_hw6_boardClass_h

#include <iostream>
#include <fstream>
using namespace std;
template <class T>

struct Card {
	T info;
	bool status;
	Card ()
	{
		status = false;
	}
	Card (T info)
	{
	status = false;
	}
};


template <class T>
class Board 
{
	private:
		Card<T> ** arrayMatrix;
		int row, column;
	public:
		 Board(int row, int column); //default constructor
		 ~Board ();   //destructor function visits all nodes and returns to heap
		 void displayBoard() const; // prints two dimensional dynamic matrix
		 void closeCard(int idxRow, int idxColumn); // change status of card to be closed (false)
		 void readBoardFromFile (ifstream& inputFile); // gets values from input file and stores in two dimensional dynamic array
		 Card<T>** getArrayMatrix () const; // accessor function which returns two dimensional array
		 int getRow() const; // accessor function which returns private member (row)
		 int getColumn() const; // accessor function which returns private member (column)
};


#include "Yasinughur_Ughur_Yasin_hw6_boardClass.cpp"
#endif