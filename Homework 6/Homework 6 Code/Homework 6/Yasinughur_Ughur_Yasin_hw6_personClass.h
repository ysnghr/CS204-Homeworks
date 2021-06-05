#ifndef Yasinughur_Ughur_Yasin_hw6_personClass_h
#define Yasinughur_Ughur_Yasin_hw6_personClass_h

#include "Yasinughur_Ughur_Yasin_hw6_boardClass.h"

template <class T>
class Player 
{
	private:
		int score;
		Board<T> & board;
	public:
		 Player(Board<T>& board); // constructor
		 T openCard(int idxRow, int idxColumn); // changes status to true (opened)
		 bool validMove(int idxRow, int idxColumn) const; // checks conditions of index of row and column
		 void increaseNumberOfSuccess();  // increses private member
		 int getNumberOfSuccess() const;  // accessor function which returns score (private member)
};


#include "Yasinughur_Ughur_Yasin_hw6_personClass.cpp"
#endif