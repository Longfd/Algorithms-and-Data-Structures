#pragma once

// linked stack derived from chain
// derived from abstract class stack just to make sure 
// all methods of the ADT are implemented

#include "chainWithIterator.h"
#include "stack.h"
#include "myException.h"

template<typename T>
class derivedLinkedStack : private chain<T>, public stack<T>
{
public:
	derivedLinkedStack() {}
	~derivedLinkedStack() {}

	bool empty() const override { return chain<T>::empty(); }

	int size() const override { return chain<T>::size(); }

	T& top() override 
	{
		if (chain<T>::empty())
			throw stackEmpty();
		return chain<T>::get(0);
	}

	void pop() override 
	{ 
		if (chain<T>::empty())
			throw stackEmpty();
		return chain<T>::erase(0);
	}

	void push(const T& theElement) override { return chain<T>::insert(0, theElement); }
};

void derivLinkStackTest();
