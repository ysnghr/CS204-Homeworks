#include <iostream>
#include "Yasinughur_Ughur_Yasin_hw6_boardClass.h"
using namespace std;

//default constructor
template <class T>
Board<T>::Board (int rowParam, int columnParam)
{
	row = rowParam;
	column = columnParam;
	arrayMatrix = new Card<T> *[row];

	for (int i = 0; i < row; i++)
	{
		arrayMatrix[i] = new Card<T> [column];
	}
}

//destructor function visits all nodes and returns to heap
template <class T>
Board<T>::~Board ()
{
    for (int i = 0; i < row; i++) {
        delete[] arrayMatrix[i];
    }
    delete[] arrayMatrix;
	row = 0;
	column = 0;
}

// accessor function which returns private member (row)
template <class T>
int Board<T>::getRow() const
{
	return row;
}

// accessor function which returns private member (column)
template <class T>
int Board<T>::getColumn() const
{
	return column;
}	

// prints two dimensional dynamic matrix
template <class T>
void Board<T>::displayBoard() const
{
    for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++)
		{
			// if the card is opened then print its value
			if (arrayMatrix[i][j].status == true)
			{
				cout << arrayMatrix[i][j].info << " ";
			}
			else
			{
				cout << "X" << " ";
			}
			
		}
		cout << endl;
    }
}

// change status of card to be closed (false)
template <class T>
void Board<T>::closeCard (int idxRow, int idxColumn)
{
	arrayMatrix[idxRow][idxColumn].status = false;
}

// accessor function which returns two dimensional array
template <class T>
Card<T>** Board<T>::getArrayMatrix () const
{
	return arrayMatrix;
}

// gets values from input file and stores in two dimensional dynamic array
template <class T>
void Board<T>::readBoardFromFile (ifstream& inputFile)
{
	// iterator for row
	for (int i = 0; i < row; i++)
	{
		string line;
		T word;
		getline(inputFile,line);
		stringstream ss(line);
		// iterator for each cell value
		for (int j = 0; j < column; j++)
		{
			ss >> word;
			arrayMatrix[i][j].info = word;
			// status will be closed
			arrayMatrix[i][j].status = false;
		}
	}

}