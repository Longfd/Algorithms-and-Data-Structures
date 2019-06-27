#pragma once

// a queue implemented with singly-linked list
// derives from the ADT	queue

#include "queue.h"
#include "chainNode.h"
#include "myException.h"
#include <sstream>

template<typename T>
class linkedQueue : private chainNode<T>, public queue<T>
{
public:
	linkedQueue() :
		_front(0), _back(0), _queueSize(0)
	{
	}
	~linkedQueue() 
	{
		chainNode<T>* p = 0;
		while (_front != 0)
		{
			p = _front->next;
			delete _front;
			_front = p;
		}
	}

	// ADT methods
	bool empty() const { return _queueSize == 0; }

	int size() const { return _queueSize; }

	T& front() {
		if (empty())
			throw queueEmpty();
		return _front->element;
	}

	T& back() {
		if (empty())
			throw queueEmpty();
		return _back->element;
	}

	void pop(){
		if (empty())
			throw queueEmpty();
		chainNode<T>* p = _front->next;
		delete _front;
		_front = p;
		--_queueSize;
	}

	void push(const T& theElement)
	{
		if (empty())
			_front = _back = new chainNode<T>(theElement, 0);
		else 
			_back = _back->next = new chainNode<T>(theElement, 0);
		
		++_queueSize;
	}

private:
	chainNode<T>* _front;
	chainNode<T>* _back;
	int _queueSize;
};

void linkedQueueTest();
