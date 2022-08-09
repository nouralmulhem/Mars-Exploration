

#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_

#include "Node.h"
#include <vector>
using namespace std;


template <typename T>
class LinkedQueue
{
private :
	int count;
	Node<T>* backPtr;
	Node<T>* frontPtr;
public :
	LinkedQueue();	
	bool isEmpty() const ;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);  
	bool peek(T& frntEntry)  const;	
	int getcount() const;
	~LinkedQueue();

	//copy constructor
	LinkedQueue(const LinkedQueue<T> & LQ);
};
/////////////////////////////////////////////////////////////////////////////////////////


template <typename T>
LinkedQueue<T>::LinkedQueue()
{
	backPtr=nullptr;
	frontPtr=nullptr;
	count = 0;
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return (frontPtr==nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool LinkedQueue<T>::enqueue( const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	count++;
	return true ;
}



template <typename T>
bool LinkedQueue<T>:: dequeue(T& frntEntry)  
{
	if(isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr ;	
		
	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	count--;
	return true;

}
/////////////////////////////////////////////////////////////////////////////////////////




template <typename T>
bool LinkedQueue<T>:: peek(T& frntEntry) const 
{
	if(isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}

template <typename T>
int LinkedQueue<T>::getcount() const
{
	return count;
}
///////////////////////////////////////////////////////////////////////////////////




template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	T temp;
	
	//Free (Dequeue) all nodes in the queue
	while(dequeue(temp));	
	count = 0;
}


template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T> & LQ)
{	
	count = LQ.count;
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
}

#endif