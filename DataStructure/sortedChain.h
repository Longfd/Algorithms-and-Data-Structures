#pragma once

// sorted chain, implement dictionary

#include <iostream>
#include "dictionary.h"
#include "pairNode.h"

void sortedChainTest();

template<class K, class E>
class sortedChain : public dictionary<K, E>
{
public:
	sortedChain() { firstNode = 0; dSize = 0; }
	~sortedChain();

	bool empty() const { return dSize == 0; }
	int size() const { return dSize; }
	std::pair<const K, E>* find(const K&) const;
	void erase(const K&);
	void insert(const std::pair<const K, E>&);
	void output(std::ostream& out) const;

protected:
	pairNode<K, E>* firstNode;
	int dSize;
};

template<class K, class E>
sortedChain<K, E>::~sortedChain()
{
	pairNode<K, E>* nextNode = 0;
	while (firstNode != 0)
	{
		nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template<class K, class E>
std::pair<const K, E>* sortedChain<K, E>::find(const K& theKey) const
{
	pairNode<K, E>* currentNode = firstNode;
	while (currentNode != 0)
	{
		if (currentNode->element.first == theKey)
			return &(currentNode->element);
		else
			currentNode = currentNode->next;
	}

	return nullptr;
}

template<class K, class E>
void sortedChain<K, E>::erase(const K& theKey)
{
	pairNode<K, E>* prev = 0;
	pairNode<K, E>* p = firstNode;
	
	while (p != nullptr && p->element.first < theKey)
	{
		prev = p;
		p = p->next;
	}

	if (p != nullptr && p->element.first == theKey)
	{
		if (prev == 0) // p is first node
			firstNode = p->next;
		else
			prev->next = p->next;

		delete p;
		--dSize;
	}
}

template<class K, class E>
void sortedChain<K, E>::insert(const std::pair<const K, E>& thePair)
{
	pairNode<K, E>* p = firstNode;
	pairNode<K, E>* prev = nullptr;
	while (p != nullptr && p->element.first < thePair.first) {
		prev = p;
		p = p->next;
	}

	// check if there is a matching pair
	if (p != NULL && p->element.first == thePair.first)
	{// replace old value
		p->element.second = thePair.second;
		return;
	}

	if (prev == 0) // first node
		firstNode = new pairNode<K, E>(thePair, p);
	else
		prev->next = new pairNode<K, E>(thePair, p);

	++dSize;
}

template<class K, class E>
void sortedChain<K, E>::output(std::ostream& out) const
{
	pairNode<K, E>* p = firstNode;
	for(; p != nullptr; p = p->next)
		out << "<" << p->element.first << ", "
			<< p->element.second << "> ";
}

template<class K, class E>
std::ostream& operator << (std::ostream& out, const sortedChain<K, E>& right) {
	right.output(out);
	return out;
}
