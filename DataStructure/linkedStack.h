#pragma once

// stack implement with linked List
// derived from ADT stack

#include "chainNode.h"
#include "stack.h"
#include "myException.h"
#include <assert.h>

template<typename T>
class linkedStack : public stack<T>, private chainNode<T>
{
public:
	linkedStack() : _stackSize(0), _top(0) 
	{
	}
	~linkedStack();

	bool empty() const { return _stackSize == 0; }

	int size() const { return _stackSize; }

	T& top() 
	{
		if (empty())
			throw stackEmpty();
		return _top->element;
	}

	void pop();

	void push(const T& theElement)
	{
		_top = new chainNode<T>(theElement, _top);
		++_stackSize;
	}

private:
	int _stackSize;
	chainNode<T>* _top;
};

template<typename T>
linkedStack<T>::~linkedStack()
{
	chainNode<T>* p = 0;

	while (_top != nullptr)
	{
		p = _top->next;
		delete _top;
		_top = p;
	}
}

template<typename T>
void linkedStack<T>::pop()
{
	if (empty())
		throw stackEmpty();

	chainNode<T>* p = _top->next;
	delete _top;
	_top = p;
	--_stackSize;
}

void linkedStackTest();
