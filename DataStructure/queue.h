#pragma once

// abstract class queue
// abstract data type specification for queue data structure
// all methods are pure virtual functions

template<typename T>
class queue {
public:
	virtual ~queue() = default;

	virtual bool empty() const = 0;

	virtual int size() const = 0;

	virtual T& front() = 0;

	virtual T& back() = 0;

	virtual void pop() = 0;

	virtual void push(const T& theElement) = 0;
};