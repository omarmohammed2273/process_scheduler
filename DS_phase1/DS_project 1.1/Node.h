
#ifndef _NODE
#define _NODE
template < typename T>
class Node
{
protected:
	T item; // A data item
	Node<T>* next; // Pointer to next node
public:
	Node(){next = nullptr;}
	Node(const T& r_Item)
	{
		item = r_Item;
		next = nullptr;
	}
	Node(const T& r_Item, Node<T>* nextNodePtr)
	{
		item = r_Item;
		next = nextNodePtr;
	}
	void setItem(const T& r_Item){item = r_Item;}
	void setNext(Node<T>* nextNodePtr){next = nextNodePtr;}
	T getItem() {return item;}
	Node<T>* getNext() {return next;}
}; // end Node
#endif
/*
template < typename T>
Node<T>::Node()
{

}

template < typename T>
Node<T>::Node(const T& r_Item)
{

}

template < typename T>
Node<T>::Node(const T& r_Item, Node<T>* nextNodePtr)
{

}
template < typename T>
void Node<T>::setItem(const T& r_Item)
{
	
}

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	
}

template < typename T>
T Node<T>::getItem() const
{
	
}

template < typename T>
Node<T>* Node<T>::getNext() const
{
	
}
*/