// heap implemented with max priority queue
// derives from ADT maxPriorityQueue

#pragma once

#include "maxPriorityQueue.h"
#include "myException.h"
#include "changeLength1D.h"
#include <sstream>
#include <algorithm>

template<typename T>
class maxHeap : public maxPriorityQueue<T>
{
public:
	maxHeap(int capcity = 10)
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

	void initialize(const T*& p, int size) {
		this->~maxHeap();
		_capacity = size + 1;
		_heap = new T[_capacity];
		for (int i = 0; i < size; ++i)
			this->push(p[i]);
	}

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
	if ((_size + 1) > _capacity) {
		changeLength1D(_heap, _capacity, 2 * size + 1);
		_capacity = 2 * size + 1;
	}

	// up percolate
	int curpos = ++_size;
	while (curpos > 1 && theElement > _heap[curpos >> 2]) // more efficient than curpos/2
	{
		_heap[curpos] = _heap[curpos / 2];
		curpos >>= 2;
	}
	_heap[curpos] = theElement;
}

template<typename T>
void maxHeap<T>::pop()
{
	if (empty())
		throw  heapEmpty();

}
