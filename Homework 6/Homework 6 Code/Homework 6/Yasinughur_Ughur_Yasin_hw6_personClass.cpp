#include <iostream>
#include "Yasinughur_Ughur_Yasin_hw6_personClass.h"
using namespace std;

//constructor
template <class T>
Player<T>::Player (Board<T>& paramBoard):board(paramBoard), score(0)
{
}

// changes status to true (opened)
template <class T>
T Player<T>::openCard (int idxRow, int idxColumn)
{
	board.getArrayMatrix()[idxRow][idxColumn].status = true;
	return board.getArrayMatrix()[idxRow][idxColumn].info;
}

// checks two condition:
// idxRow and idxColumn is in matrix or not
// and the card opened or not
template <class T>
bool Player<T>::validMove(int idxRow, int idxColumn) const
{
	if (idxRow <= board.getRow() - 1 && idxRow <= board.getColumn() - 1 && idxRow >=  0 && idxColumn >= 0 && board.getArrayMatrix()[idxRow][idxColumn].status == false)
	{
		return true;
	}
	return false;
}

// increses private member
template <class T>
void Player<T>::increaseNumberOfSuccess()
{
    score++;
}

// accessor function which returns score (private member)
template <class T>
int Player<T>::getNumberOfSuccess() const
{
	return score;
}	