#pragma once

// node type used in skip lists
// node with a next and element field; element is a paire<const K, E>
// next is a 1D array of pointers

#include <utility>

template<class K, class E>
class skipNode
{
public:
	typedef std::pair<const K, E> pairType;

	skipNode(const pairType& thePair, int size)
		: element(thePair)
	{
		next = new skipNode<K, E>* [size];
	}


	pairType element;
	skipNode<K, E>** next; // 1D array of pointers
};
