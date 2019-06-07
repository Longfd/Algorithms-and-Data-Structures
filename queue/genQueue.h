//********************** genQueue.h **********************
// generic queue implementation with doubly-linked list
#ifndef DLL_QUEUE
#define DLL_QUEUE

#include <list>

template<T>
class Queue {
public:
	T dequeue() {
		T el = lst.front();
		lst.pop_front();
		return el;
	}

	void enqueue(const T& el) {
		lst.push_back(el);
	}

private:
	std::list<T> lst;
};
