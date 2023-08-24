 #ifndef _LINKEDLIST
#define _LINKEDLIST
#include<iostream>
using namespace std;
#include "Node.h"

template <typename T>
class LinkedList
{
public:
	Node<T> *Head;	//Pointer to the head of the list
	Node<T> *Tail;
	int size;
	//You can add tail pointer too (depending on your problem)

public:
	Node<T>* getHead() { return Head; }
	int get_size()
	{
		return size;
	}

	void Print()
	{
		Node<T>* p = Head;
		while (p)
		{
			cout << " ";
			cout << p->getItem();
			p = p->getNext();
			cout << ",";

		}
	}
	
	

	LinkedList()
	{
		Head = nullptr;
		Tail = nullptr;
		size = 0;
	}
	//copy constructor
	LinkedList(LinkedList &copy)
	{
		if(copy.Head == nullptr)
		{
			Head = nullptr;
			return ;
		}
		Node<T> *new_node = new Node<T>(copy.Head->getItem());
		Head = new_node;
		Node<T> *temp1 = copy.Head->getNext();
		Node<T> *temp2 = Head;
		while(temp1)
		{
			Node<T> *new_node = new Node<T>(temp1->getItem());

			temp2->setNext(new_node);
			temp2 = temp2->getNext();
			temp1 = temp1->getNext();
		}
		Tail = temp2;
		size = copy.size;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll(); 
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	/*
	void PrintList() const
	{
		Node<T> *p = Head;
		while(p)
		{
			cout << p->getItem();
			p = p->getNext();
			if(p)
				cout<<" ";

		}
		cout << "NULL\n";
	}*/
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	* 
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
		size++;

	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T> *P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
		size = 0;
	}



	////////////////     Requirements   ///////////////////
	//
	// Implement the following member functions


	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T &data)
	{
		Node<T> *new_node = new Node<T>(data);
		if(!Head)
		{
			Head = new_node;
			Tail = new_node;
			size++;
			return ;
		}
		Tail->setNext(new_node);
		Tail = Tail->getNext();
		size++;
		return ;
	}

	//[2]Find 
	//searches for a given value in the list, returns true if found; false otherwise.
	bool Find(int Key);

	//[3]CountOccurance
	//returns how many times a certain value appeared in the list
	int CountOccurance(const T &value);

	//[4] DeleteFirst
	//Deletes the first node in the list
	bool DeleteFirst(T &value)
	{
		if(!Head)
			return false;
		Node<T> *temp = Head;
		value = Head->getItem();
		if(Tail==Head)
			Tail = Head->getNext();
		Head = Head->getNext();
		delete temp;
		size--;
		return true;
	}


	//[5] DeleteLast
	//Deletes the last node in the list
	void DeleteLast();

	//[6] DeleteNode
	//deletes the first node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNode(const T &value)
	{
		if(Head==nullptr)
			return false;
		Node<T> *temp = Head;
		if(temp->getItem()==value)
		{
			Head=temp->getNext();
			delete temp;
			size--;
			return true;
		}
		Node<T> *pre = temp;
		temp = temp->getNext();
		while (temp)
		{
			if(temp->getItem()==value)
			{
				pre->setNext(temp->getNext());
				delete temp;
				size--;
				return true;
			}
			pre = temp;
			temp = temp->getNext();
		}
		return false;
	}

	//[7] DeleteNodes
	//deletes ALL node with the given value (if found) and returns true
	//if not found, returns false
	//Note: List is not sorted
	bool DeleteNodes(const T &value);	

	//[8]Merge
	//Merges the current list to another list L by making the last Node in the current list 
	//point to the first Node in list L
	void Merge(const LinkedList& L);

	//[9] Reverse
	//Reverses the linked list (without allocating any new Nodes)
	void Reverse();

	//[10] isEmpty
	//check if the linked list is empty or not
	bool isEmpty()
	{return !Head;}
	

};


#endif	
