// abstract class priority queue
// all methods are pure virtual functions

#pragma once

template<typename T>
class priorityQueue
{
public:
	priorityQueue() = default;
	virtual ~priorityQueue() = default;

	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual const T& front() = 0;
	virtual void push(const T& theElement) = 0;
	virtual void pop() = 0;
};
