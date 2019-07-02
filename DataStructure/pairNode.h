#pragma once

// node with a next and element field; element is a pair<const K, E>

#include <utility>

template <class K, class E>
struct pairNode
{
	typedef std::pair<const K, E> pairType;
	pairType element;
	pairNode<K, E> *next;

	pairNode(const pairType& thePair, pairNode<K, E>* theNext = 0) :
		element(thePair),
		next(theNext)
	{
	}
};
