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
	maxHeap()
		:_heap(nullptr),
		_size(0),
		_capacity(0)
	{
	}
	maxHeap(T* a, int size)
	{
		_heap = new T[size + 1];
		for (int i = 0; i < size; ++i)
			_heap[i + 1] = a[i];

		_size = 0;
		_capacity = size + 1;
	}
	~maxHeap() 
	{
		delete[] _heap;
		_size = _capacity = 0;
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

}

template<typename T>
void maxHeap<T>::push(const T& theElement)
{

}

template<typename T>
void maxHeap<T>::pop()
{

}
