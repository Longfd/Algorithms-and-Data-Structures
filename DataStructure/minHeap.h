// min heap implemented with priority queue
// derived from ADT class priorityQueue

#pragma once

#include "priorityQueue.h"
#include "changeLength1D.h"
#include "myException.h"
#include <algorithm>
#include <iostream>

void minHeapTest();

template <typename T>
class minHeap : public priorityQueue<T>
{
public:
	minHeap(int capacity = 5)
		:_heap(0),
		_size(0),
		_capacity(capacity)
	{
		_heap = new T[_capacity];
	}
	~minHeap()
	{
		delete [] _heap;
		_capacity = _size = 0;
	}

	// ADT methods
	bool empty() const { return _size == 0; }
	int size() const { return _size; }
	const T& front() {
		if (_size == 0)
			throw heapEmpty();
		return _heap[1];
	}
	void push(const T& theElement);
	void pop();

	// other func
	void initialize(T* a, int size);
	void sort();
	void heapify();
	void output(std::ostream& out) const;

protected:
	T* _heap;
	int _size;
	int _capacity;
};

template <typename T>
void minHeap<T>::push(const T& theElement)
{
	if (_size + 1 == _capacity) {
		changeLength1D(_heap, _capacity, 2 * _capacity);
		_capacity *= 2;
	}

	// percolate up
	int curpos = ++_size;
	int parent = curpos / 2;
	while (parent >= 1)
	{
		// if we can put theElement at curpos
		if (_heap[parent] <= theElement)
			break;
		_heap[curpos] = _heap[parent]; // move down parent
		curpos = parent; // move up curpos
		parent = parent / 2;
	}
	_heap[curpos] = theElement;
}

template <typename T>
void minHeap<T>::pop()
{
	if (_size == 0)
		throw heapEmpty();

	T lastElement = _heap[_size--];

	// percolate down
	int curpos = 1;
	int child = curpos * 2;
	while (child <= _size)
	{
		// childNode should be smaller child of currentNode
		if (child < _size && _heap[child] > _heap[child + 1])
			child++;

		// if we can put lastElement at curpos
		if (_heap[child] >= lastElement)
			break;
		_heap[curpos] = _heap[child];
		curpos = child;
		child *= 2;
	}
	_heap[curpos] = lastElement;
}

template <typename T>
void minHeap<T>::initialize(T* a, int size)
{
	this->~minHeap();
	_capacity = size + 1;
	_heap = new T[_capacity];
	for (int i = 0; i < size; ++i)
		push(a[i]);
}

template <typename T>
void minHeap<T>::sort()
{
	int sizeTmp = _size;
	while (sizeTmp > 1)
	{
		std::swap(_heap[1], _heap[sizeTmp--]);
		T topElement = _heap[1];
		
		// percolate down
		int curpos = 1;
		int child = curpos * 2;
		while (child <= sizeTmp)
		{
			if (child < sizeTmp && _heap[child] > _heap[child + 1])
				child++;
			if (_heap[child] >= topElement)
				break;
			_heap[curpos] = _heap[child];
			curpos = child;
			child *= 2;
		}
		_heap[curpos] = topElement;
	}
}

template <typename T>
void minHeap<T>::heapify()
{
	int root = _size / 2;

	for (int i = root; root <= 1; root--)
	{
		T value = _heap[root];

		// percolate down
		int curpos = root;
		int child = curpos * 2;
		while (child <= _size)
		{
			if (child < _size && _heap[child] > _heap[child + 1])
				++child;
			if (_heap[child] >= value)
				break;
			_heap[curpos] = _heap[child];
			curpos = child;
			child *= 2;
		}
		_heap[curpos] = value;
	}
}

template <typename T>
void minHeap<T>::output(std::ostream& out) const
{
	for (int i = 1; i < _size; ++i)
		out << _heap[i] << " ";
	out << std::endl;
}

// overload <<
template <typename T>
std::ostream& operator<<(std::ostream& out, const minHeap<T>& right)
{
	right.output(out);
	return out;
}
