#include <iostream>
#include <string>
#include "Yasinughur_Ughur_Yasin_hw5_class.h"

using namespace std;

// constructor of Wallet class
Wallet::Wallet(){
	size = 0;
	moneys = NULL;
}

// second constructor of Wallet class
Wallet::Wallet(int sizeparam){
	size = sizeparam;
	moneys = new Money[sizeparam];
}

// deconstructor of Wallet class
Wallet::~Wallet(){
	size = 0;
	delete[] moneys;
	moneys = NULL;
}

// deep copy constructor of Wallet class
Wallet::Wallet(const Wallet &copy){
	size = copy.size;
	moneys = new Money[size];

	for (int i = 0; i < size; i++)
	{
		moneys[i].amount = copy.moneys[i].amount;
		moneys[i].currency = copy.moneys[i].currency;
	}
}

int Wallet::getSize() const
// postcondition: return size
{
    return size;
}

Money* Wallet::getMoneys() const
// postcondition: return dynamic array
{
    return moneys;
}

// == operator
const Wallet& Wallet::operator= (const Wallet & rhs)
{
	if (this != &rhs)
	{
		size = 0;
		// deletes the left side
		delete[] moneys;
		

		size = rhs.size;
		moneys = new Money[size];

		// adding right side
		for (int i = 0; i < size; i++)
		{
			moneys[i] = rhs.moneys[i];
		}
	}
	return *this;
}

// adds right side wallet to left side wallet
Wallet Wallet::operator+(const Wallet &rhs) const
{
	// finding new size of new wallet object
	int sizeFix = this->findNewSize(rhs);
	Wallet result(sizeFix);
	result.size = sizeFix;

	// adding left size to new dynamic array
	for (int i = 0; i < size; i++)
	{
		result.moneys[i].currency = moneys[i].currency;
		result.moneys[i].amount = moneys[i].amount;
	}

	int extendAdd = size;

	// adds moneys that are in right side while is not in left side
	for (int i = 0; i < rhs.size; i++)
	{
		bool check = false;
		for (int b = 0; b < size; b++)
		{
			// if it is in left side just adds the amount
			if (rhs.moneys[i].currency == moneys[b].currency)
			{
				check = true;
				result.moneys[b].amount += rhs.moneys[i].amount;
				result.moneys[b].currency = rhs.moneys[i].currency; 
			}
		}
		// if it is not in left side adds it
		if (check == false)
		{
			result.moneys[extendAdd].amount = rhs.moneys[i].amount;
			result.moneys[extendAdd].currency = rhs.moneys[i].currency;
			extendAdd++;
		}
	}

	return result;
}

bool Wallet::Equals(const Wallet& c) const
{
	if (size == c.size)
	{
		for (int i = 0; i < size; i++)
		{
			bool find = false;
			for (int j = 0; j  < c.size; j ++)
			{
				if (moneys[i].amount == c.moneys[j].amount && moneys[i].currency == c.moneys[j].currency)
				{
					find = true;
				}
			}

			if (find == false)
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}
	return true;
}

// iterates over wallet if currency equals and amount is lower then returns true
bool Wallet::isExists(const Money& c) const
{
	for (int i = 0; i < size; i++)
	{
		if (moneys[i].currency == c.currency&& moneys[i].amount >= c.amount)
		{
			return true;
		}
	}
	return false;
}

// iterates over two wallets if the content of them is equal then returns true
bool operator == (const Wallet& lhs, const Wallet& rhs)
{
    return lhs.Equals(rhs);
}

// iterates over wallet if currency equals and amount is lower then returns true
bool operator >= (const Wallet& lhs, const Money& rhs)
{
	return lhs.isExists(rhs);
}

// iterates over wallet if currency equals and amount is higher then returns true
bool operator <= (const Money& lhs, const Wallet& rhs)
{
	for (int i = 0; i < rhs.getSize(); i++)
	{
		if (rhs.getMoneys()[i].currency == lhs.currency && lhs.amount <= rhs.getMoneys()[i].amount)
		{
			return true;
		}
	}
	return false;
}

// as you know a += b is a = a + b
// for this reason i used + operator in this function
Wallet  operator += (Wallet& lhs, const Wallet& rhs)
{
	lhs = lhs + rhs; 
	return lhs;
}

// printing wallet objects datas
ostream& operator << (ostream& os, const Wallet &ct)
{
	Money* arr = ct.getMoneys();

	for (int i = 0; i < ct.getSize(); i++)
	{
		if (i != ct.getSize() - 1)
		{
			os << arr[i].currency << " " << arr[i].amount << " - ";
		}
		else
		{
			os << arr[i].currency << " " << arr[i].amount;
		}
	}
	return os;
}

// adds money to wallet
// we have two condition
// 1. money exists in wallet we just need to increase the amount
// 2. money does not exists in wallet and we need to add it to our dynamic array
Wallet Wallet::operator+(const Money &rhs) const
{

	bool exists = false;
	int index = 0;
	// iterating over dynamic array for just checking the money exists or not
	for (int i = 0; i < size; i++)
	{
		if (rhs.currency == moneys[i].currency)
		{
			exists = true;
			index = i;
		}
	}

	// if it is existing then it means that we will not change the size of dynamic array
	if (exists)
	{
		Wallet result(size);
		for (int i = 0; i < size; i++)
		{
			// just adding the amount to wallet
			if (rhs.currency == moneys[i].currency)
			{
				result.moneys[i].amount = moneys[i].amount + rhs.amount;
				result.moneys[i].currency = rhs.currency;
			}
			else
				// adding eveything else
			{
				result.moneys[i].amount = moneys[i].amount;
				result.moneys[i].currency = moneys[i].currency;
			}
		}
		return result;
	}
	else
	// if it is not exist in dynamic array we need to just increase size of dynamic array
	{
		Wallet result(size+1);
		if (size == 0)
		{
			result.moneys[0].amount = rhs.amount;
			result.moneys[0].currency = rhs.currency;
		}
		else
		{
			// adds everything else
			for (int i = 0; i < size; i++)
			{
				result.moneys[i].amount = moneys[i].amount;
				result.moneys[i].currency = moneys[i].currency;
			}

			// at the end of the dynamic array add new money
			result.moneys[size].amount = rhs.amount;
			result.moneys[size].currency = rhs.currency;
		}
		return result;
	}
}

// compares two wallet objects
// and finds identical the number of moneys
int Wallet::findNewSize(const Wallet &rhs) const
{
	int sizeCounter = size;
	// finding moneys that are not in the left side while it is in the right side
	for (int i = 0; i < rhs.size; i++)
	{
		bool check = false;
		for (int j = 0; j < size; j++)
		{
			if (rhs.moneys[i].currency == moneys[j].currency)
			{
				// if the currency is in two sides then there is no need to other values
				// that is why i break here
				check = true;
				break;
			}
		}
		// if it is not exists in left side then it means that it is new value
		// for this reason we need to increase the size of dynamic array
		if (check == false)
		{
			sizeCounter += 1;
		}
	}

	return sizeCounter;
}

// deletes money from wallet object
Wallet Wallet::operator-(const Money &rhs) const
{
	// if the money object's currency amount is equal to wallet object currency amount 
	// then we need to delete it from wallet object
	bool isDeleted = false;
	for (int i = 0; i < size; i++)
	{
		if (moneys[i].currency == rhs.currency && rhs.amount == moneys[i].amount)
		{
			isDeleted = true;
		}
	}

	// if we need to delete something from dynamic array we need to decrease the size of dynamic array
	if (isDeleted)
	{
		Wallet result(size-1);
		bool add = false;
		for (int i = 0; i < size; i++)
		{
			if (moneys[i].currency != rhs.currency || add)
			{
	 			if (add)
	 			{
	 				result.moneys[i - 1].amount = moneys[i].amount;
	 				result.moneys[i - 1].currency = moneys[i].currency;
	 			}
	 			else
				// adds everything else
	 			{
	 				result.moneys[i].amount = moneys[i].amount;
	 				result.moneys[i].currency = moneys[i].currency;
	 			}
			}
			// skips
			else if(moneys[i].currency == rhs.currency && rhs.amount == moneys[i].amount)
			{
				add = true;
			}
		}
		return result;
	}
	else
	// this condition we just need to decrease the amount of currency if it is less than wallet amount
	{
		Wallet result(size);
		for (int i = 0; i < size; i++)
		{
			if (rhs.currency == moneys[i].currency && rhs.amount < moneys[i].amount)
			{
				result.moneys[i].currency = moneys[i].currency;
				result.moneys[i].amount = moneys[i].amount - rhs.amount;
			}
			else
			{
				result.moneys[i].amount = moneys[i].amount;
				result.moneys[i].currency = moneys[i].currency;
			}
		}
		return result;
	}
}