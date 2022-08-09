


#ifndef LINKED_PRI_QUEUE_
#define LINKED_PRI_QUEUE_

#include"Node_pri.h"
#include <vector>
using namespace std;


template <typename T , typename X>
class LinkedQueue_pri
{
private:
	int count;
	Node_pri<T, X>* backPtr;
	Node_pri<T,X>* frontPtr;
public:
	LinkedQueue_pri();
	bool isEmpty() const;
	bool enqueue(const T& newEntry, X priority);
	bool dequeue(T& frntEntry);
	bool peek(T& frntEntry)  const;
	int getcount() const;
	~LinkedQueue_pri();

	//copy constructor
	LinkedQueue_pri(const LinkedQueue_pri<T,X>& LQ);
};
/////////////////////////////////////////////////////////////////////////////////////////


template <typename T,typename X>
LinkedQueue_pri<T,X>::LinkedQueue_pri()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	count = 0;
}



template <typename T, typename X>
bool LinkedQueue_pri<T,X>::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////


template <typename T, typename X>
bool LinkedQueue_pri<T,X>::enqueue(const T& newEntry, X priority)
{
	Node_pri<T, X>* newNodePtr = new Node_pri<T, X>(newEntry, priority);

	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
	{
		// creating new pointer to traverse the list 
		Node_pri<T, X>* movingptr = frontPtr;

		if (newNodePtr->getPriority() > frontPtr->getPriority())
		{
			// in case the new inseted node has the highest priority 
			// we make it the head of the list to be deququed first
			newNodePtr->setNext(frontPtr);
			frontPtr = newNodePtr;
		}
		else
		{
			// traversing to know where to put the node depending on its priority
			while (movingptr->getNext() != NULL && newNodePtr->getPriority() <= movingptr->getNext()->getPriority())
				movingptr = movingptr->getNext();
			// insertig the new node in its right position 
			newNodePtr->setNext(movingptr->getNext());
			movingptr->setNext(newNodePtr);
		}
	}
	count++;
	return true;
} 



template <typename T, typename X>
bool LinkedQueue_pri<T,X>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node_pri<T,X>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = nullptr;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;
	count--;
	return true;

}
/////////////////////////////////////////////////////////////////////////////////////////



template <typename T, typename X>
bool LinkedQueue_pri<T,X>::peek(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}

template <typename T,typename X>
int LinkedQueue_pri<T,X>::getcount() const
{
	return count;
}

///////////////////////////////////////////////////////////////////////////////////


template <typename T, typename X>
LinkedQueue_pri<T,X>::~LinkedQueue_pri()
{
	T temp;

	//Free (Dequeue) all nodes in the queue
	while (dequeue(temp));
	count = 0;
}




template <typename T, typename X>
LinkedQueue_pri<T,X>::LinkedQueue_pri(const LinkedQueue_pri<T,X>& LQ)
{
	count = LQ.count ;
	Node_pri<T,X>* NodePtr = LQ.frontPtr;

	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	Node_pri<T, X>* ptr = new Node_pri<T, X>(NodePtr->getItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->getNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node_pri<T,X>* ptr = new Node_pri<T,X>(NodePtr->getItem());
		backPtr->setNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->getNext();
	}
}

#endif