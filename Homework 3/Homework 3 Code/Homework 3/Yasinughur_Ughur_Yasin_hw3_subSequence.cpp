#include <iostream>
#include "Yasinughur_Ughur_Yasin_hw3_subSequence.h"

using namespace std;

// constructor of SubSeqsList class
SubSeqsList::SubSeqsList(){
	// new node which should be equal to hHead
	SubSeqHeadNode *newNode = new SubSeqHeadNode();
	hHead = newNode;
}

// checking hHead next is empty or not
bool SubSeqsList::checkEmptyHhead() const
{
	if (hHead->next == NULL)
	{
		return true;
	}
	return false;
}

// printing overall hybrid linkedlist
void SubSeqsList::displayStructure() const{
	cout << endl << "FINAL CONTENT" << endl;
	SubSeqHeadNode *  ptr = hHead->next;   // loop variable
	
	// if hHead next is null then we have not any subsets
	if (hHead->next == NULL)
	{
		cout << "List is empty!"  << endl;
		return;
	}
	while(ptr != NULL)
	{
		cout << ptr->size << " | ";
		SubSeqNode *rowPtr = ptr->sHead;
		if (rowPtr->next == NULL)
		{
			cout << rowPtr->value;
		}
		else
		{
			while (rowPtr != NULL)
			{
				// check for the next value
				// if I have next value I need to print one more --> sign
				if (rowPtr->next == NULL)
				{
					cout << rowPtr->value;
				}
				else
				{
					cout << rowPtr->value << " --> ";
				}
				
				rowPtr = rowPtr->next;
			}
		}
		cout << endl;
		ptr = ptr->next;
	}
}

/* Begin: code taken from ptrfunc.cpp */
void DeleteOneNode (SubSeqHeadNode * toBeDeleted, SubSeqHeadNode * & head)
/* pre: toBeDeleted points to the node to be deleted from the list
   post: deletes the node pointed by toBeDeleted, updates head if changes */
{
	SubSeqHeadNode * ptr;
		
	if (toBeDeleted == head)  //if the node to be deleted is the first node
	{
		head = head->next;
		delete toBeDeleted;
	}
	else  //if the node to be deleted is in the middle or at the end
	{
		ptr = head;
		while (ptr->next != toBeDeleted)
			ptr = ptr->next;
		//after while ptr point to the node just before toBeDeleted

		//connect the previous node to the next node and delete
		ptr->next = toBeDeleted->next;
		delete toBeDeleted;
	}
}
/* End: code taken from ptrfunc.cpp */

void SubSeqsList::deleteSubSeqs(int num)
{
	// changing sign for finding the numbers from our subseqnode linkedlist
	num = num * -1;
	SubSeqHeadNode *  ptr = hHead->next;   // loop variable
	SubSeqHeadNode * deletedHead;
	bool existsOverall = false; // at least one value that exists in our linkedlist it will be true
	while(ptr != NULL)
	{
		SubSeqNode *rowPtr = ptr->sHead;
		bool exists = false; // this is for subseqnode search
		while (rowPtr != NULL)
		{
			if (rowPtr->value == num)
			{
				deletedHead = ptr;
				exists = true;
				existsOverall = true;
			}
			rowPtr = rowPtr->next;
		}

		if (exists == true)
		{
			SubSeqNode *head = deletedHead->sHead;
			while(head != NULL)
			{
				SubSeqNode *ptrDel = head;
				head = head->next;
				delete ptrDel;
			}
			ptr = ptr -> next;
			DeleteOneNode(deletedHead, hHead->next);
		}
		else
		{
			ptr = ptr->next;
		}
	}

	if (existsOverall == false)
	{
		cout << "There is no subsequence that contains "<< num <<" to be deleted"<<endl;
	}
	else
	{
		cout << "All subsequence(s) containing "<<num<<" has/have been deleted"<<endl;
	}
}

bool SubSeqsList::checkExists(int num) const
{
	SubSeqHeadNode *  ptr = hHead->next;   // loop variable
	SubSeqHeadNode * deletedHead;
	bool exists = false;
	while(ptr != NULL)
	{
		// just searching from subseqheadnodes which have just one subseqnode
		if (ptr->size == 1)
		{
			SubSeqNode *rowPtr = ptr->sHead;
			while (rowPtr != NULL)
			{
				if (rowPtr->value == num)
				{
					exists = true;
					cout << num <<" is already in the list!" << endl;
					return exists;
				}
				rowPtr = rowPtr->next;
			}
		}
		ptr = ptr->next;
	}
	
	return exists;
}

// compares two headnodes
bool SubSeqsList::findAddOrder(SubSeqHeadNode *willAdd, SubSeqHeadNode *compareOne) 
{
	if (willAdd->size > compareOne->size)
	{
		return true;
	}
	// if linkedlist node's size is bigger than new node(compareOne) then we need to stop (give false)
	else if (willAdd->size < compareOne->size)
	{
		return false;
	}
	
	SubSeqNode *ptr1 = willAdd->sHead; // loop variable
	SubSeqNode *ptr2 = compareOne->sHead; // loop variable
	bool equal = true;
	// we know that they are same size and for this reason we can iterate over one of them
	while(ptr1 != NULL)
	{
		// we need to control equality of each value of the linkedlist 
		if (equal == false)
		{
			return false;
		}

		// checks next if there is not next value and new node is bigger than ptr next then continue(give true)
		if (ptr1->next == NULL && ptr1->value > ptr2->value && equal)
		{
			return true;
		}

		if (ptr1->next != NULL && ptr1->value > ptr2->value && equal)
		{
			return true;
		}


		// if they are not equal equal will be false
		if (ptr1->value != ptr2->value)
		{
			equal = false;
		}

		// next values
		ptr1 = ptr1->next; 
		ptr2 = ptr2->next;

	}
	return false;
}

/* Begin: code taken and updated from ptrfunc.cpp */
SubSeqHeadNode * SubSeqsList::AddInOrder(SubSeqHeadNode * head, SubSeqHeadNode *newkey)
// pre: list is sorted
// post: add newkey to list, keep list sorted, return head of new list with newkey in it
{
	if (head->sHead->value > newkey->sHead->value)
	{
		newkey->next = head;
		head = newkey;
	}
	else
	{
		SubSeqHeadNode *  ptr = head;   // loop variable
		// check node one ahead so we don't pass!
		while (ptr->next != NULL && findAddOrder(newkey, ptr->next))
		{   
			ptr = ptr->next;
		} // postcondition: new node to be inserted just after the node that ptr points

		//now insert node with newkey after where ptr points to
		newkey->next = ptr->next; //connect the rest
		ptr->next = newkey;
	}

    return head;
}
/* End: code taken and updated from ptrfunc.cpp */

// insert one or more subsequence list(s) to the data structure
void SubSeqsList::insertSubSeqs(int num) 
{
	cout << "Subsequence(s) containing "<< num <<" has/have been added" << endl;

	// checking it is first addition or not
	if (checkEmptyHhead())
	{
		SubSeqNode *subseqNode = new SubSeqNode(num);
		SubSeqHeadNode *newNode = new SubSeqHeadNode(1, subseqNode);
		hHead->next = newNode;
	}
	else
	{
		// find subsequences
		SubSeqNode *subseqNode = new SubSeqNode(num);
		SubSeqHeadNode *newNode = new SubSeqHeadNode(1, subseqNode);
		hHead->next = AddInOrder(hHead->next, newNode);
		SubSeqHeadNode *i = hHead->next;   // loop variable

		int counter = 0;
		while(i != NULL)
		{
			SubSeqNode *j = i->sHead; // loop variable

			// finding tail of the subseqnode list
			while (j->next != NULL)
			{
				j = j->next;
			}

			// copy subseqheadnode data and add our num to the end of the linkedlist
			SubSeqHeadNode *newRowData = new SubSeqHeadNode();
			SubSeqHeadNode *copyFromHere = i;


			// incrementing the size variable of the subseqheadnode
			newRowData->size = copyFromHere->size + 1;
			
			SubSeqNode *copyFromHeresHead = i->sHead->next;
			
			// initializting new subseqnode
			SubSeqNode *newRowDatasHead = new SubSeqNode(copyFromHere->sHead->value);
			newRowData->sHead = newRowDatasHead;
			while (copyFromHeresHead != NULL)
			{
				newRowDatasHead->next = new SubSeqNode(copyFromHeresHead->value);
				copyFromHeresHead = copyFromHeresHead->next;
				newRowDatasHead = newRowDatasHead->next;
			}

			// checking the tail is less than num or not
			if (j->value < num)
			{
				newRowDatasHead->next = new SubSeqNode(num);
				hHead->next = AddInOrder(hHead->next, newRowData);
			}
			
			i = i->next;
			counter++;
		}
	}
}

// deletes all nodes from our program
void SubSeqsList::deleteAll()
{
	SubSeqHeadNode *  ptr = hHead->next;   // loop variable
	
	// iterating over subseqheadnodes
	while(ptr != NULL)
	{
		SubSeqNode *rowPtr = ptr->sHead;

		// iterating over subseqnodes
		while (rowPtr != NULL)
		{
			SubSeqNode *deletedNode = rowPtr;
			rowPtr = rowPtr->next;
			// deleting subseqnode
			delete deletedNode;
		}

		// deleting subseqheadnode
		SubSeqHeadNode *deletedHead = ptr;
		ptr = ptr->next;
		delete deletedHead;
	}
}