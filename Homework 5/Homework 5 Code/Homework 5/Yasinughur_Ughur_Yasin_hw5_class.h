#ifndef Yasinughur_Ughur_Yasin_hw5_class_h

#define Yasinughur_Ughur_Yasin_hw5_class_h
#include <string>
using namespace std;
struct Money
{
	string currency;
	double amount;
};class Wallet
{
	public:
		Wallet(); //default constructor that creates an empty list
		Wallet(int sizeparam); // gets size and creates dynamic array with this size
		~Wallet(); // deconstructor
		Wallet(const Wallet &copy); // deep copy constructor of Wallet class
		const Wallet& operator=(const Wallet &copy); // equalize left side to right side wallet obj
		Wallet operator+(const Money &) const; // adds money to wallet
		Wallet operator+(const Wallet &) const; // adds right side wallet to left side wallet
		Wallet operator-(const Money &) const; // deletes money from wallet
		bool Equals(const Wallet& ct) const; // iterates over two wallets for checking they equal or not
		bool isExists(const Money& ct) const; // iterates over wallet if currency equals and amount is lower then returns true
		int getSize() const; // getter function which returns size
		Money* getMoneys() const; // getter function which returns money (dynamic array)
		int findNewSize(const Wallet& ct) const; // finds new size for dynamic array
	private:
		Money* moneys;
		int size;
};

ostream &  operator << (ostream & os, const Wallet & ct); // printing wallet objects datas
bool operator ==  (const Wallet& lhs, const Wallet& rhs); // iterates over two wallets if the content of them is equal then returns true
bool operator <= (const Money& lhs, const Wallet& rhs); // iterates over wallet if currency equals and amount is higher then returns true
Wallet operator += ( Wallet& lhs, const Wallet& rhs); // a = a + b  a+=b
bool operator >= (const Wallet& lhs, const Money& rhs); // iterates over wallet if currency equals and amount is higher then returns true

#endif /* Yasinughur_Ughur_Yasin_hw5_class_h */