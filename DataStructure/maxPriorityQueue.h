// abstract class max priority queue
// all methods are pure virtual functions

#pragma once

template<typename T>
class maxPriorityQueue
{
public:
	maxPriorityQueue() = default;
	virtual ~maxPriorityQueue() = default;

	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual const T& front() = 0;
	virtual void push(const T& theElement) = 0;
	virtual void pop() = 0;
};
