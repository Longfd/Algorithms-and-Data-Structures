//******************* intSLList.cpp *******************
#include <iostream>
#include "intSLList.h"

IntSLList::~IntSLList() {
	for(IntSLLNode*p = NULL; !isEmpty();) {
		p = head -> next;
		delete head;
		head = p;
	}
}

void IntSLList::addToHead(int el) 
{
	head = new IntSLLNode(el, head);
	if(tail == 0)
		tail = head;
}

void IntSLList::addToTail(int el)
{
	if(tail == 0) {
		head = tail = new IntSLLNode(el, 0);
	}
	else {
		tail = tail->next = new IntSLLNode(el, 0);
	}
}

int IntSLList::deleteFromHead()
{
	int el = head->info;
	IntSLLNode* tmp = head->next;
	delete head;
	head = tmp;

	if(head == 0)
		tail = 0;
	return el;
}

int IntSLList::deleteFromTail()
{
	int el = tail->info;
	IntSLLNode*p = head;

	if(p == tail) {
		delete tail;
		head = tail = 0;
	}
	else{
		for(IntSLLNode* p = head; p->next != tail; p = p->next) 
		delete tail;
		tail = p;
		tail->next = 0;
	}

	return el;
}

void IntSLList::deleteNode(int el)
{
	IntSLLNode*p = head;

	if(p->info == el) {
		deleteFromHead();
		return;
	}

	for(; p->next != 0; p = p->next) {
		if(p->next->info == el) {
			if(p->next == tail) {
				deleteFromTail();
				return;
			}
			IntSLLNode* tmp = p->next;
			p->next = tmp->next;
			delete(tmp);
		}
	}
}

bool IntSLList::isInList(int el)const
{
	for(IntSLLNode*p = head; p != 0 && (p->info != el); p = p->next)

	return p != 0;
}
