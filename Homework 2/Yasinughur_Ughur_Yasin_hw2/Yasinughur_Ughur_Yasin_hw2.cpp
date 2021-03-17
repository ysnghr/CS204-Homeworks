/*-------------------------------------------------------

Faculty of Engineering and Natural Sciences
CS204 Advanced Programming
Spring 2021
Homework: Displaying Sorted Subsequences with Linked Lists
Input: getting input from user

Output: Printing results for each case

Author: Yasin Ughur

Date: 3/17/2021

---------------------------------------------------------*/

#include <iostream>
#include <sstream>

using namespace std;

struct node
{
	int value;
	node* next;

	node::node(const int &s, node *link) : value(s), next (link)
	{}
};

// gets first word from text (string) and checking whether it is ascending or descending
bool checkOrder(string text)
{
	istringstream wordSelector(text);
	string word;

	// here I have return in the while which means that this while
	// will work only once for just only first word
	while(wordSelector >> word)
	{
		if (word == "A")
		{
			return false;
		}
		else if(word == "D")
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	return false;
}

string getOrderMode()
{
	string input;
	cout << "Please enter the order mode (A/D): ";
	// every time I am reading the line as input
	getline(cin, input);

	// then I am checking input check (get first word and check whether is A or D)
	while(checkOrder(input))
	{
		cout << "Please enter the order mode again (A/D): ";
		getline(cin, input);
	}

	// if the given input is correct then i am returing it from this function
	istringstream wordSelector(input);
	string word;
	while(wordSelector >> word)
	{
		return word;
	}
}

// Gets numbers as string from user
string getNumbers()
{
	cout << "Please enter the numbers in a line: ";
	string line;
	getline(cin, line);
	return line;
}

// Adds newkey to end of the linked list
node* AddNode(node *head, int newkey, string orderMode)
{
	node *ptr = head;

	// If the order is ascending and head is null or the number that will 
	// be added is smaller than the exists one in the linkedlist then we need to replace it with new number

	// if ordermode is opposite (descending) then same thing will be happen
	if (orderMode == "A")
	{
		if(head == NULL || newkey < head->value)
		{
			return new node(newkey, head);
		}
	}
	else if(orderMode == "D")
	{
		if(head == NULL || newkey > head->value)
		{
			return new node(newkey, head);
		}
	}

	// iterating over linkedlist
	while(ptr->next != NULL)
	{
		ptr = ptr->next;
	}

	// adding newkey to end of the linkedlist
	ptr->next  = new node(newkey, ptr->next);
	return head;
}

bool checkEquality(node *head, int number, string orderMode)
{
	node *ptr = head;
	if (head != NULL)
	{
		// if the order is ascending the I need to check all numbers is smaller than the new number
		// for checking this situation i iterated over the linkedlist
		if (orderMode == "A")
		{
			while (ptr != NULL)
			{
				if (ptr->value >= number)
				{
					return true;
				}
				ptr = ptr->next;
			}
		}
		// same operation done for descending one but here there is opposition version of the sign
		else
		{
			while (ptr != NULL)
			{
				if (ptr->value <= number)
				{
					return true;
				}
				ptr = ptr->next;
			}
		}
	}

	return false;
}

// delete some numbers from linked list if the linkedlist not in sorted way
node* deleteLinkedListAndPrint(node *head, node *nodeStart, string orderMode)
{
	// nodeStart is a node which violates the order
	node *temp = head;

	// if
	if(nodeStart == head)
	{
		// deleting all nodes from linkedlist
		while(nodeStart	!= NULL)
		{
			cout << " " << nodeStart->value;
			head = nodeStart->next;
			delete nodeStart;
			nodeStart = head;
		}
		return head;
	}
	else
	{
		// iterating over linkedlist with ptr to reach nodestart (the node which violates order)
		node * ptr = head;
		while(ptr->next != nodeStart)
		{
			ptr = ptr->next;
		}

		while(nodeStart	!= NULL)
		{
			cout << " " << nodeStart->value;
			ptr->next = nodeStart->next;
			delete nodeStart;
			nodeStart = ptr->next;
		}
	}

	return temp;
}

// printing each result after getting number from user
node* printEach(int nextNumber, string orderMode , bool isDeleted, int appended, node *head, node *nodeStart, bool equalOrNot)
{
	cout << endl;
	cout << "Next number: " << nextNumber << endl;

	// checking entered number is equal to any number in the list
	if (equalOrNot == false)
	{
		if (isDeleted)
		{
			cout << "Deleted nodes:";
			head = deleteLinkedListAndPrint(head, nodeStart, orderMode);
			cout << endl;
		}
		else
		{
			cout << "Deleted nodes: None" << endl;
		}

		cout << "Appended: " << appended << endl;
		head = AddNode(head, appended, orderMode);
	}
	else
	{
		cout << nextNumber << " is already in the list!" << endl;
	}


	cout << "List content:";

	// iterating over the linkedlist for printing its content
	node *ptr = head;
	while (ptr != NULL)
	{
		cout << " " << ptr->value;
		ptr = ptr->next;
	}
	cout << endl;
	return head;
}

// here I am returing the node which violates order
// e.g 4 8 10 12 9 (ascending order) here the function will return  10 because
// 10 violates the order
node *findStartOfDeletion(string orderMode, node *head, int number)
{
	node *ptr = head;
	// if the order is ascending
	if (orderMode == "A")
	{
		while (ptr != NULL)
		{
			if (ptr->value >= number)
			{
				return ptr;
			}
			ptr = ptr->next;
		}
	}
	else
		// if the order is descending
	{
		while (ptr != NULL)
		{
			if (ptr->value <= number)
			{
				return ptr;
			}
			ptr = ptr->next;
		}
	}
}

// prints linkedlist at the end of the program and deletes all pointers
void printLinkedList(node *head)
{
	cout << endl << "All the nodes are deleted at the end of the program:";
	while(head != NULL)
	{
		node *ptr = head;
		cout << " " << head->value;
		head = head->next;
		delete ptr;
	}
	cout << endl;
}

// gets number as string from getNumbers function
// with the help of streams gets each one by one and sends to other functions
void loopOverString(string numbers, node *head, string orderMode)
{
	istringstream stream(numbers);
	int number;
	while(stream >> number)
	{
		bool equalOrNot = false;
		// first here I am checking that 
		if (checkEquality(head, number, orderMode))
		{
			node *nodeStart = findStartOfDeletion(orderMode, head, number);
			if(nodeStart->value == number)
			{
				equalOrNot = true;
			}
			head = printEach(number, orderMode , true, number, head, nodeStart, equalOrNot);
		}
		else
		{
			node *nodeStart = NULL;
			// here I am sending false (isDeleted) because if there is not any problem for adding the number to linkedlist
			// i will not delete something
			head = printEach(number, orderMode, false, number, head, nodeStart, equalOrNot);
		}
	}

	// prints linkedlist at the end of the program
	printLinkedList(head);
}

// with stringstream checks the line is empty or not
bool checkLineIsEmpty(string text)
{
	istringstream stream(text);
	int i = 0;
	while(stream >> text)
	{
		i += 1;
		break;
	}
	//if it is zero returns false, otherwise true
	return (i == 0) ? false : true;
}

int main()
{
	node *head = NULL;
	string orderMode = getOrderMode();
	string numbers = getNumbers();


	if (checkLineIsEmpty(numbers))
	{
		loopOverString(numbers, head, orderMode);
	}
	else
		// if the line is empty the program prints message and then stops
	{
		cout << endl << "The list is empty at the end of the program and nothing is deleted" << endl;
	}
}