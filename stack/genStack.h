//********************** genStack.h **********************
// generic class for vector implementation of stack

#ifndef STACK
#define STACK

#include <vector>

template<T, int capacity = 30>
class Stack {
public:
	Stack(){ pool.reserve(capacity); }

	void clear() { pool.clear(); }
	bool isEmpty() { return pool.empty(); }
	T pop() {
		T el = pool.back();
		pool.pop_back();
		return el;
	}
	void push(const T& el) { pool.push_back(el); }

private:
	std::vector<T> pool;
};

#endif
