//******************* genDLList.h *******************
// doubly-linked class with generic 

#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

template<class T>
class DLLNode{
public:
	DLLNode():
		info(), prev(0), next(0)
	{}
	DLLNode(const T& el, DLLNode* p = 0, DLLNode* n = 0):
		info(el), prev(p), next(n)
	{}
	~DLLNode();

	T info;
	T* prev;
	T* next;
};

template class<T>
class DoublyLinkedList {
public:
	DoublyLinkedList() :
		head(0), tail(0)
	{}
	void addToDLLTail(const T& el)
	{
		if(tail == 0) {
			head = tail = new DLLNode(el, 0 , 0);
		}
		else {
			tail = new DLLNode(el, tail, 0);
			tail->prev->next = tail;
		}
	}

	T deleteFromDLLTail()
	{
		T el = tail->info;
		if(head == tail) {
			delete tail;
			head = tail = 0;
		}
		else {
			tail = tail->prev;
			delete tail->next;
			tail->next = 0;
		}
		return el;
	}

protected:
	DLLNode* head;
	DLLNode* tail;
}

#endif
