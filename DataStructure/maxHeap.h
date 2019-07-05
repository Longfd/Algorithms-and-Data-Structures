// heap implemented with max priority queue
// derives from ADT maxPriorityQueue

#pragma once

#include "maxPriorityQueue.h"
#include "myException.h"
#include "changeLength1D.h"
#include <sstream>
#include <algorithm>

void maxHeapTest();

template<typename T>
class maxHeap : public maxPriorityQueue<T>
{
public:
	maxHeap(int capcity = 5)
		:_heap(nullptr),
		_size(0),
		_capacity(capcity)
	{
		_heap = new T[_capacity];
	}
	~maxHeap() 
	{
		delete[] _heap;
		_size = _capacity = 0;
	}

	void initialize(T*& p, int size) {
		this->~maxHeap();
		_capacity = size + 1;
		_heap = new T[_capacity];
		for (int i = 0; i < size; ++i)
			this->push(p[i]);
	}
	void sort(T*& dest, int size);
	void heapify();

	// ADT methods
	bool empty() const override { return _size == 0; }
	int size() const override { return _size; }
	const T& front() override;
	void push(const T& theElement) override;
	void pop() override;

protected:

	T* _heap;
	int _size;
	int _capacity;
};

template<typename T>
const T& maxHeap<T>::front()
{
	if (empty())
		throw  heapEmpty();
	return _heap[1];
}

template<typename T>
void maxHeap<T>::push(const T& theElement)
{
	if ((_size + 1) == _capacity) {
		changeLength1D(_heap, _capacity, 2 * _capacity);
		_capacity *= 2;
	}

	// up percolate
	int curpos = ++_size;
	while (curpos > 1) 
	{
		bool bSwap = false;
		if (theElement > _heap[curpos >> 1]) { // more efficient than curpos/2
			_heap[curpos] = _heap[curpos / 2];
			curpos >>= 1; 
			bSwap = true;
		}
		if (!bSwap)
			break;
	}
	_heap[curpos] = theElement;
}

template<typename T>
void maxHeap<T>::pop()
{
	if (empty())
		throw  heapEmpty();

	T lastElement = _heap[_size--];

	// percolate down
	int curpos = 1;
	int childpos = curpos * 2;
	while (childpos <= _size)
	{
		// heap[child] should be larger child of currentNode
		if (childpos < _size && _heap[childpos] < _heap[childpos + 1]) 
			childpos++;

		// if we can put lastElement at curpos
		if (lastElement >= _heap[childpos])
			break;

		_heap[curpos] = _heap[childpos]; // move child up
		curpos = childpos; // move down a level
		childpos *= 2;
	}
	_heap[curpos] = lastElement;
}

template<typename T>
void maxHeap<T>::sort(T*& dest, int size)
{
	if (empty())
		throw heapEmpty();

	while (size > 0)
	{
		dest[size - 1] = _heap[1];
		T lastElement = _heap[size];
		std::swap(_heap[1], _heap[size--]);

		// percolate down
		int curpos = 1;
		int childpos = curpos * 2;
		while (childpos <= size)
		{
			// heap[childpos] should be larger child node of heap[curpos]
			if (childpos < size && _heap[childpos] < _heap[childpos + 1])
				childpos++;
			
			// if we can put lastElement at curpos
			if (_heap[childpos] <= lastElement)
				break;

			// move child up
			_heap[curpos] = _heap[childpos];
			curpos = childpos;
			childpos *= 2;
		}
		_heap[curpos] = lastElement;
	}
}

template<typename T>
void maxHeap<T>::heapify()
{
	int curpos = _size >> 1;

	for (; curpos >= 1; curpos--) 
	{
		T curElement = _heap[curpos];
		int child = curpos * 2;

		while (child <= _size)
		{
			if (child < _size && _heap[child] < _heap[child + 1])
				child++;
			if (_heap[child] <= curElement)
				break;

			_heap[curpos] = _heap[child];
			curpos = child;
			child *= 2;
		}
		_heap[curpos] = curElement;
	}
}
