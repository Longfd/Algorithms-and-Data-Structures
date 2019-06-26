#pragma once

#include "queue.h"
#include "myException.h"
#include <sstream>


template<typename T>
class arrayQueue : public queue<T>
{
public:
	arrayQueue(int initialCapacity = 5)
	{
		if (initialCapacity <= 0) {
			std::ostringstream oss;
			oss << "arrayQueue: capacity[" << initialCapacity << "] must be > 0";
			throw illegalParameterValue(oss.str());
		}

		_queue = new T[initialCapacity];
		_length = initialCapacity;
		_front = 0;
		_back = 0;
	}
	~arrayQueue() { delete[] _queue; }

	// ADT methods
	bool empty() const { return _front == _back; }

	int size() const { return (_back - _front + _length) % _length; }

	T& front() {
		if(_front == _back)
			throw queueEmpty();
		return _queue[(_front + 1) % _length];
	}

	T& back() {
		if (_front == _back)
			throw queueEmpty();
		return _queue[_back];
	}

	void pop() {
		if (empty())
			throw queueEmpty();
		_front = (_front + 1) % _length;
		_queue[_front].~T();  // destructor for T
	}

	void push(const T& theElement);

private:
	int _length;
	int _front;
	int _back;
	T* _queue;
};

template<typename T>
void arrayQueue<T>::push(const T& theElement)
{
	// check
	if ((_back + 1) % _length == _front) {
		T* tmp = new T[2 * _length];
		
		int start = (_front + 1) % _length;
		if (start < 2) {
			std::copy(_queue + start, _queue + start + _length - 1, tmp);
		}
		else {
			std::copy(_queue + start, _queue + _length, tmp);
			std::copy(_queue, _queue + _back + 1, tmp + _length - start);
		}

		_front = 2 * _length - 1;
		_back = _length - 1;
		_length *= 2;
		delete[] _queue;
		_queue = tmp;
	}

	_back = (_back + 1) % _length;
	_queue[_back] = theElement;
}

void arrayQueueTest();
