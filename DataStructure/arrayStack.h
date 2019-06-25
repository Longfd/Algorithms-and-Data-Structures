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

	void push(const T& theElement) override;

private:
	int stackTop; // current top of stack
	int arrayLength;
	T* stack;
};

template<typename T>
arrayStack<T>::arrayStack(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	stack = new T[arrayLength];
	stackTop = -1;
}

template<typename T>
T& arrayStack<T>::top()
{
	if (stackTop == -1)
		throw stackEmpty();

	return stack[stackTop];
}

template<typename T>
void arrayStack<T>::pop()
{
	if (stackTop == -1)
		throw stackEmpty();

	stack[stackTop--].~T();
}

template<typename T>
void arrayStack<T>::push(const T& theElement)
{
	if (stackTop == arrayLength - 1)
      {// no space, double capacity
         changeLength1D(stack, arrayLength, 2 * arrayLength);
         arrayLength *= 2;
      }

   // add at stack top
   stack[++stackTop] = theElement;
}
