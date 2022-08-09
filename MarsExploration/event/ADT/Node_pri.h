
#ifndef _NODE_PRI
#define _NODE_PRI

template < typename T , typename X>
class Node_pri
{
private:
	X priority; // the priority of the item
	T item; // A data item
	Node_pri<T,X>* next; // Pointer to next node
public:
	Node_pri();
	Node_pri(const T& r_Item, const X& pri);
	Node_pri(const T& r_Item, Node_pri<T,X>* nextNodePtr);
	Node_pri(const T& r_Item, X& pri, Node_pri<T,X>* nextNodePtr);
	void setItem(const T& r_Item);
	void setNext(Node_pri<T,X>* nextNodePtr);
	void setPriority(X& pri);
	T getItem() const;
	X getPriority() const;
	Node_pri<T,X>* getNext() const;
}; // end Node
#endif

template < typename T,typename X>
Node_pri<T,X>::Node_pri()
{
	next = nullptr;
}

template < typename T, typename X>
Node_pri<T,X>::Node_pri(const T& r_Item, const X& pri)
{
	priority = pri;
	item = r_Item;
	next = nullptr;
}

template < typename T, typename X>
Node_pri<T,X>::Node_pri(const T& r_Item, Node_pri<T,X>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}
template<typename T , typename X>
Node_pri<T ,X>::Node_pri(const T& r_Item, X& pri, Node_pri<T,X>* nextNodePtr)
{
	item = r_Item;
	priority = pri;
	next = nextNodePtr;
}
template < typename T, typename X>
void Node_pri<T,X>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T, typename X>
void Node_pri<T,X>::setNext(Node_pri<T,X>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T, typename X>
void Node_pri<T,X>::setPriority(X& pri)
{
	priority = pri;
}

template < typename T, typename X>
T Node_pri<T,X>::getItem() const
{
	return item;
}

template < typename T, typename X>
X Node_pri<T,X>::getPriority() const
{
	return priority;
}

template < typename T, typename X>
Node_pri<T,X>* Node_pri<T,X>::getNext() const
{
	return next;
}