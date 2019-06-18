#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "linearList.h"
#include "exception.h"
#include "chainNode.h"

template<typename T>
class chain : public linearList<T>
{
public:
	chain(int capacity = 10);
	chain(const chain<T>&);
	~chain();

	//ADT(Abstract Data Type) methods
	bool empty() const override;

	int size() const override;

	T& get(int index) const override;

	int indexOf(const T& element) const override;

	void erase(int index) override;

	void insert(int index, const T& element) override;

	void output(std::ostream& out) const override;

	// iterators to start and end of list
	class iterator;
	iterator& begin() { return iterator(header->next); }
	iterator& begin() { return iterator(NULL); }

	// iterator for chain
	class iterator
	{
	public:
		// typedefs required by C++ for a forward iterator
		typedef std::forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		// constructor
		iterator(chainNode<T>* node) : position(node) {}

		// dereferencing operators
		T& operator*() const { return node->element; }
		T* operator->() const { return &node->element; }

		// increment
		iterator& operator++()   // preincrement
		{
			node = node->next; return *this;
		}
		iterator operator++(int) // postincrement
		{
			iterator old = *this;
			node = node->next;
			return old;
		}

		// equality testing
		bool operator!=(const iterator right) const
		{
			return node != right.node;
		}
		bool operator==(const iterator right) const
		{
			return node == right.node;
		}

	private:
		chainNode<T>* node;
	};

protected:

	chainNode<T>* header;
	int listSize;
};

template<typename T>
chain<T>::chain(int capacity)
{

}

template<typename T>
chain<T>::chain(const chain<T>&)
{

}

template<typename T>
chain<T>::~chain()
{

}


//ADT(Abstract Data Type) methods
template<typename T>
bool chain<T>::empty() const
{

}

template<typename T>
int chain<T>::size() const
{

}

template<typename T>
T& chain<T>::get(int index) const
{

}

template<typename T>
int chain<T>::indexOf(const T& element) const
{

}

template<typename T>
void chain<T>::erase(int index)
{

}

template<typename T>
void chain<T>::insert(int index, const T& element)
{

}

template<typename T>
void chain<T>::output(std::ostream& out) const
{

}