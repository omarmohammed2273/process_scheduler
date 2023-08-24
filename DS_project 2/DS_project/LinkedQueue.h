
/*
This is a program that implements the queue abstract data type using a linked list.
The queue is implemented as a chain of linked nodes that has two pointers,
a frontPtr pointer for the front of the queue and a backPtr pointer for the back of the queue.
*/

/*

The Node: item of type T and a "next" pointer
-------------
| item| next | --->
-------------
General Queue case:

frontPtr																backPtr
\											   						/
\											  					   /
------------- 	  ------------- 	  ------------- 	  -------------
| item| next |--->| item| next |--->  | item| next |--->  | item| next |---> NULL
------------- 	  ------------- 	  ------------- 	  -------------

Empty Case:

frontptr	 backptr
\	 /
\	/
---- NULL ------


Single Node Case:
frontPtr	 backPtr
\		/
\	   /
-----------
|item| next| -->NULL
-----------

*/
#include "LinkedList.h"
#include "QueueADT.h"
#include <vector>
#include "Process.h"





#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_

using namespace std;


template <typename T>
class LinkedQueue :public QueueADT<T>
{
protected:
	Node<T>* backPtr;
	Node<T>* frontPtr;
	int size;

public:
	Node<T>* getFrontPtr();
	LinkedQueue();
	bool isEmpty() const;
	virtual bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	~LinkedQueue();
	void Print();
	int get_size();
	//copy constructor
	LinkedQueue(const LinkedQueue<T>& LQ);
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/
template <typename T>
int LinkedQueue<T>::get_size()
{
	return size;
}
template <typename T>
Node<T>* LinkedQueue<T>::getFrontPtr()
{
	return frontPtr;
}
template <typename T>
void LinkedQueue<T>::Print() 
{
	Node<T>* p = frontPtr;
	while (p)
	{
		cout << " ";
		 cout << p->getItem();
		p = p->getNext();
		if(p)
			cout << ",";
		
	}

}
/*
template <>
void LinkedQueue<Process *>::Print()
{
	Node<Process*>* p = frontPtr;
	while (p)
	{
		cout << " ";
		cout << p->getItem()->get_PID();
		p = p->getNext();

		cout << ",";

	}

}*/
template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	size = 0;
}



/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool LinkedQueue<T>::enqueue(const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	size++;
	return true;
} // end enqueue


  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  /*Function: dequeue
  Removes the front of this queue. That is, removes the item that was added
  earliest.

  Input: None.
  Output: True if the operation is successful; otherwise false.
  */

template <typename T>
bool LinkedQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	size--;
	return true;

}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/
template <typename T>
bool LinkedQueue<T>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////
/*
Function: destructor
removes all nodes from the queue by dequeuing them
*/
template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: Copy constructor
To avoid shallow copy,
copy constructor is provided

Input: LinkedQueue<T>: The Queue to be copied
Output: none
*/

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& LQ)
{
	Node<T>* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	Node<T>* ptr = new Node<T>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node<T>* ptr = new Node<T>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
	size = LQ.size;
}

#endif
