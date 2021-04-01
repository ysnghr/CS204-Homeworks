#ifndef Yasinughur_Ughur_Yasin_hw3_subSequence_h
#define Yasinughur_Ughur_Yasin_hw3_subSequence_h

struct SubSeqNode
{
	int value;
	SubSeqNode * next;
	
	// constructors come here
	SubSeqNode::SubSeqNode (const int & s, SubSeqNode * link)
		: value(s), next (link)
	{
	}

	SubSeqNode::SubSeqNode (int num)
	{
		value = num;
		next = NULL;
	}
};

struct SubSeqHeadNode
{
	int size; // number of elements in the subsequence
	SubSeqNode * sHead; // head of the subsequence list
	SubSeqHeadNode * next;
	// constructors come here

	SubSeqHeadNode::SubSeqHeadNode ()
	{
		size = 0;
		sHead = NULL;
		next = NULL;
	}

	SubSeqHeadNode::SubSeqHeadNode (const int & s, SubSeqNode * link)
		: size(s), sHead (link)
	{
		next = NULL;
	}


	SubSeqHeadNode::SubSeqHeadNode (const int & s, SubSeqHeadNode * link)
		: size(s), next (link)
	{
		next = NULL;
	}

};

class SubSeqsList
{
	public:
		SubSeqsList(); //default constructor that creates an empty list
		
		void displayStructure() const;	// displays the entire structure
		void insertSubSeqs(int num);			// insert one or more subsequence list(s) to the data structure
		void deleteSubSeqs(int num);			// delete one or more subsequence list(s) from the data structure
		bool checkExists(int num) const;		// o find whether a particular value exists in the data structure
		void deleteAll();						// delete the entire data structure
		bool checkEmptyHhead() const;			// checking hHead next is empty or not
		bool findAddOrder(SubSeqHeadNode *willAdd, SubSeqHeadNode *compareOne);		// compares two headnodes
		SubSeqHeadNode * AddInOrder(SubSeqHeadNode * head, SubSeqHeadNode *newkey); // adds headnode to headnode linkedlist

		// member functions come here
	private:
		SubSeqHeadNode * hHead;
		// any helper functions you see necessary
};

#endif /* Yasinughur_Ughur_Yasin_hw3_subSequence_h */