/*-------------------------------------------------------

Purpose: The aim is to put given words into a matrix letter by letter.

Input: .txt files

Output: Printing array

Author: Yasin Ughur

Date: 3/4/2021


---------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// this function makes a vector which consist of two integers that are given in the file
vector<int> getArraySize(ifstream& input)
{
	int row, col;
	input >> row >> col;
	vector<int> rowCol;
	rowCol.push_back(row);
	rowCol.push_back(col);
	return rowCol;
}

// this function checks whether the file exists
string checkFileName()
{
	string filename;
	cout << "Please enter the name of the file: ";
	cin >> filename;
	ifstream input;
	input.open(filename.c_str());
	while(input.fail() == true)
	{
		cout << "File name is incorrect, please enter again: ";
		cin >> filename;
		input.open(filename.c_str());
	}
	return filename; 
}

// checking the two inputs that are in the beginning of the file whether they are positive or not
bool checkRowAndCol(vector<int> vec)
{
	if(vec[0] <= 0 || vec[1] <= 0)
	{
		return true;
	}
	return false;
}

// here I printed vector of vector of strings (my matrix) on console
void printVec(vector<vector<string>> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j  < vec[i].size(); j ++)
		{
			cout << vec[i][j] << " ";
		}
		cout << endl;
	}
}

// this function gets vector of string which contains the line's words
// and then returns true if there is not enough data
bool checkSize(vector<string> vec)
{

	if (vec.size() != 5)
	{
		return true;
	}
	return false;
}

// checks each line parametrs one by one.
// 1. starting point
// 2. direction
// 3. orientation
bool checkCaseLine(vector<string> vec, vector<int> rowAndcol)
{
	int row = atoi(vec[1].c_str());
	int col = atoi(vec[2].c_str());
	if((0 > row) || (row > rowAndcol[0]-1))
	{
		cout << "Starting point is out of range! Point: " << row << "," << col << endl;
		return true;
	}
	else if((0 > col) || (col > rowAndcol[1]-1)) 
	{
		cout << "Starting point is out of range! Point: " << row << "," << col << endl;
		return true;
	}
	else if(vec[3] != "r" && vec[3] != "l" && vec[3] != "u" && vec[3] != "d")
	{
		cout << "Invalid input for direction! Direction: " << vec[3] << endl;
		return true;
	}
	else if(vec[4] != "CCW" && vec[4] != "CW")
	{
		cout << "Invalid input for orientation! Orientation: " << vec[4] << endl;
		return true;
	}
	return false;
}

// checks whether the cell occupied by another word or not
bool checkOccupy(vector<vector<string>> vec, vector<int> point)
{
	if (vec[point[0]][point[1]] != "-")
	{
		return false;
	}
	return true;
}

// here I checked whether the given cell of row and column is within the length of 0 and
// the length of the matrix
bool checkNewCell(vector<int> point, vector<int> rowAndcol)
{
	if (((0 <= point[0]) && (point[0] <= rowAndcol[0] - 1)) && ((0 <= point[1]) && (point[1] <= rowAndcol[1] - 1)))
	{
		return true;
	}
	return false;
}

// with given dimension I am updating the cell's row and column values
vector<int> getNewCell(string dir, vector<int> point)
{
	if (dir == "r")
	{
		point[1] = point[1] + 1;
	}
	else if(dir == "l")
	{
		point[1] = point[1] - 1;
	}
	else if(dir == "u")
	{
		point[0] = point[0] - 1;
	}
	else if(dir == "d")
	{
		point[0] = point[0] + 1;
	}
	return point;
}

// gets index of searched string from vector of strings
int getIndexVector(vector<string> elements, string search)
{
	for (int i = 0; i < elements.size(); i++)
	{
		if (elements[i] == search)
		{
			return i;
		}
	}
}

void placeWordonVec(vector<string> givenData, vector<vector<string>>& vec, vector<int> rowAndcol)
{
	// copied original matrix because I dont want to affect the original one
	// as you know we have some cases in which some words can not fill the matrix
	// because of that everytime I am copying the original matrix
	vector<vector<string>> copy( rowAndcol[0] , vector<string> (rowAndcol[1],  "-")); 
	copy = vec;
	
	vector<int> point;

	// initialized string array and then converted it to vector of string
	// here I did this thing because the version of C++ does not support initializing vector with values
	string tmp[] = { "u", "l", "d", "r" };
	// CCW direction flow
	vector<string> CCW( tmp, tmp+4 );

	string tmp2[] = { "d","l","u", "r" };
	// CW direction flow
	vector<string> CW( tmp2, tmp2+4 );

	point.push_back(stoi(givenData[1]));
	point.push_back(stoi(givenData[2]));

	string dir = givenData[3];

	// checking the starting point occupied or not
	// if occupied it will return and stop
	if (checkOccupy(copy, point) == false)
	{
		cout << endl << "\"" << givenData[0] <<"\" could not be put into the matrix with given starting point: "<< point[0] << "," << point[1]
		<<" direction: "<< givenData[3] <<" orientation: " << givenData[4] << endl;
		return;
	}

	copy[point[0]][point[1]] = givenData[0][0];

	// looping over the rest of word
	for (int i = 1; i < givenData[0].length(); i++)
	{

		// getting new point with direction

		// if it is not occupied the program will also place the word of letter to the cell
		vector<int>	newpoint = getNewCell(dir, point);
		
		if (checkNewCell(newpoint, rowAndcol) && checkOccupy(copy, newpoint))
		{
			point = newpoint;
			copy[point[0]][point[1]] = givenData[0][i];
		}
		else
		{
			bool placed = false;
			if (givenData[4] == "CCW")
			{

				int indexDir = getIndexVector(CCW, dir);
				int z = 0;
				for (int k = indexDir; k < (indexDir + CCW.size()); k++)
				{
					if (k >= 4)
					{
						z = k - 4;
					}
					else
					{
						z = k;
					}


					//find index of direction from CCW
					// then iterate over 
					// 0 1 2 3 4
					// 3, 4, 0, 1, 2
					newpoint = getNewCell(CCW[z], point);
					// get new point
					// check it is avaliable or not
					// if avaliable then get direction
					if (checkNewCell(newpoint, rowAndcol) && checkOccupy(copy, newpoint))
					{
						//dir = CCW[z];
						point = newpoint;
						copy[point[0]][point[1]] = givenData[0][i];
						placed = true;
						break;
					}
				}
				if (placed == false)
				{
					cout << endl << "\"" << givenData[0] <<"\" could not be put into the matrix with given starting point: "<< givenData[1] << "," << givenData[2]
					<<" direction: "<< givenData[3] <<" orientation: " << givenData[4] << endl;
					return;
				}
			}
			else if (givenData[4] == "CW")
			{


				int indexDir = getIndexVector(CW, dir);
				int z = 0;
				for (int k = indexDir; k < (indexDir + CCW.size()); k++)
				{
					if (k >= 4)
					{
						z = k - 4;
					}
					else
					{
						z = k;
					}

					newpoint = getNewCell(CW[z], point);
					// get new point
					// check it is avaliable or not
					// if avaliable then get direction
					if (checkNewCell(newpoint, rowAndcol) && checkOccupy(copy, newpoint))
					{
						//dir = CW[z];
						point = newpoint;
						copy[point[0]][point[1]] = givenData[0][i];
						placed = true;
						break;
					}
				}
				if (placed == false)
				{
					cout << endl << "\"" << givenData[0] <<"\" could not be put into the matrix with given starting point: "<< givenData[1] << "," << givenData[2]
					<<" direction: "<< givenData[3] <<" orientation: " << givenData[4] << endl;
					return;
				}
			}

			

		}
	}
	vec = copy;
	// we need to equalize copy vector to orignal one

	// and we have some problems with ccw and cw. look them
	cout << endl;
	cout << "\"" << givenData[0] <<"\" was put into the matrix with given starting point: "<< givenData[1] << "," << givenData[2]
	<<" direction: "<< givenData[3] <<" orientation: " << givenData[4] << endl;
}



void getFileCases(ifstream& input, vector<int> rowAndcol)
{
	string line;
	vector<vector<string>> vec( rowAndcol[0] , vector<string> (rowAndcol[1],  "-")); 
	getline(input, line);
	while(getline(input, line))
	{
		istringstream keySelector(line);

		string word;
		vector<string> givenData;

		// Here I am getting the parameters that are given in each line.
		// I am storing them in vector because of input checks.
		while (keySelector >> word)
		{
			givenData.push_back(word);
		}

		if (checkSize(givenData))
		{
			cout << "Invalid line! Number of values is different than 5." << endl;
		}
		else
		{
			if (checkCaseLine(givenData, rowAndcol) == false)
			{
				if (givenData[0] == "one")
				{
					cout << "Ads"<<endl;
				}
				placeWordonVec(givenData, vec, rowAndcol);
				printVec(vec);
			}
		}
	}
}

int main()
{
	string fileName = checkFileName();
	ifstream inputFile;
	inputFile.open(fileName.c_str());
	vector<int> rowAndcol = getArraySize(inputFile);

	if(checkRowAndCol(rowAndcol))
	{
		cout << "Invalid number for row and/or column!" << endl;
	}
	else
	{
		getFileCases(inputFile, rowAndcol);
	}
}