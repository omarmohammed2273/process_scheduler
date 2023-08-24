#include"LinkedList.h"
#include"Process.h"
#pragma once

class LinkedProcess:public LinkedQueue<Process*>
{
public:
	bool DeleteById(int Id,Process* &item)
	{
		if(isEmpty())
			return false;
		Node<Process *> *temp = frontPtr;
		if(frontPtr->getItem()->get_PID()==Id)
		{
			item = frontPtr->getItem();
			if(frontPtr==backPtr)
				backPtr = frontPtr->getNext();
			frontPtr = frontPtr->getNext();
			delete temp;
			size--;
			return true;
		}
		temp = temp->getNext();
		Node<Process *>* prev = frontPtr;
		while(temp)
		{
			if(temp->getItem()->get_PID()==Id)
			{
				if(temp==backPtr)
					backPtr = prev;
				item = temp->getItem();
				prev->setNext(temp->getNext());
				delete temp;
				size--;
				return true;
			}
			temp = temp->getNext();
			prev = prev->getNext();
		}
		return false;
	}
};
