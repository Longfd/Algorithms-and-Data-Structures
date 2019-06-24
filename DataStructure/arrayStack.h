#pragma once

// a stack implement with array
// derives from the ADT stack

#include "stack.h"
#include "myException.h"
#include "changeLength1D.h"
#include <sstream>

template<typename T>
class arrayStack : public stack<T>
{
public:
	arrayStack(int initialCapacity = 10);
	~arrayStack() { delete[] stack; }

	bool empty() const override { return stackTop == -1; }

	int size() const override { return stackTop + 1; }

	T& top() override;

	void pop() override;

	void push(const T& theElement);

private:
	int stackTop; // current top of stack
	int arrayLength;
	T* stack;
};
