#include "PriorityNode.h"
#include "LinkedQueue.h"
#include "Process.h"


//
//  ProirityQueue.h
//  PriorityQueue
//
//  Created by Youssef Bahy on 17/04/2023.
//

#ifndef ProirityQueue_h
#define ProirityQueue_h
//int MAX_SIZE = 1000;

#include <iostream>
using namespace std;

template<typename T>
class priority_node
{
public:
	T Item;
	int Priority;
	/*priority_node(int size)
	{

	}*/
};

template <class T>
class ProirityQueue
{
private:
	//data members
	priority_node<T>* A;
	int heap_size;
	int MAX_SIZE;

	//member functions
	int left(int i)
	{
		return 2 * i;
	}
	int right(int i)
	{
		return 2 * i + 1;
	}
	int parent(int i)
	{
		return i / 2;
	}

	void MAX_HEAPIFY(priority_node<T>* A, int i)
	{
		int l = left(i);
		int r = right(i);
		int largest = i;
		if (l <= heap_size && A[l].Priority > A[i].Priority)
			largest = l;
		if (r <= heap_size && A[r].Priority > A[largest].Priority)
			largest = r;
		if (largest != i)
		{
			swap(A[i], A[largest]);
			MAX_HEAPIFY(A, largest);
		}
	}
	void BUILD_MAX_HEAP()
	{
		for (int i = heap_size / 2; i >= 1; i--)
		{
			MAX_HEAPIFY(A, i);
		}
	}

public:
	ProirityQueue()
	{
		int MAX_SIZE = 1000;
		A = new priority_node<T>[MAX_SIZE];
		heap_size = 0;

	}

	ProirityQueue(priority_node<T>* tempA,int size)
	{

		A = new priority_node<T>[MAX_SIZE];
		heap_size = size;
		for (int i = 1; i <= heap_size; i++)
		{





			A[i] = copy_val;
			//A[i] = new T(tempA[i])
		}

	}


	priority_node<T> Maximum()
	{
		return A[1];
	}
	priority_node<T> Extract_Max()
	{
		if (heap_size < 1)
		{
			cout << "error heap underflow \n";
			//           exit(1); //error
		}
		priority_node<T> MAX = A[1];
		A[1] = A[heap_size];
		A[heap_size] = MAX;
		heap_size--;
		MAX_HEAPIFY(A, 1);
		return MAX;
	}
	void INCREASE_KEY(int i, int k)
	{
		if (k < A[i].Priority)
		{
			cout << "error new key is smaller than current key \n";
		}
		A[i].Priority=k;
		while (i > 1 && A[parent(i)].Priority < A[i].Priority)
		{
			swap(A[i], A[parent(i)]);
			i = parent(i);
		}
	}










	void Insert(T val,int pr)
	{
		heap_size = heap_size + 1;
		A[heap_size].Item=val;
		//this->heap_size += 5;
		A[heap_size].Priority=INT_MIN;
		INCREASE_KEY(heap_size, pr);
	}

	int get_size()
	{
		return heap_size;
	}
	bool IsEmpty()
	{
		return heap_size == 0;
	}

	void Print()
	{

		int h = heap_size;
		if (h == 2)
			int x = 8;
		for (int i = 1; i <= h; i++)
		{
			T item = Extract_Max().Item;
			if(item != nullptr)
			cout << item << ' ';

		}
		Reheap(h);
	}
	void Reheap(int h)
	{
		for (int i = 1; i <= h / 2; i++)
			swap(A[i], A[h - i + 1]);
		heap_size = h;
	}









};


#endif /* ProirityQueue_h */


