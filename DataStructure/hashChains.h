#pragma once

// hash table using sorted chains and division
// implements all dictionary methods

#include <iostream>
#include "hash.h"
#include "dictionary.h"
#include "sortedChain.h"

void hashChainsTest();

template<class K, class E>
class hashChains :public dictionary<K, E>, private sortedChain<K, E>
{
public:
	hashChains(int theDivisor = 11)
	{
		divisor = theDivisor;
		dSize = 0;

		// allocate and initialize hash table array
		table = new sortedChain<K, E>[divisor];
	}
	~hashChains() { delete[] table; }

	bool empty() const { return dSize == 0; }

	int size() const { return dSize; }

	std::pair<const K, E>* find(const K& theKey) const
	{
		return table[hash(theKey) % divisor].find(theKey);
	}

	void erase(const K& theKey)
	{
		return table[hash(theKey) % divisor].erase(theKey);
	}

	void insert(const std::pair<const K, E>& thePair)
	{
		int homeBucket = (int)hash(thePair.first) % divisor;
		int homeSize = table[homeBucket].size();
		table[homeBucket].insert(thePair);
		if (table[homeBucket].size() > homeSize) // if Key exists, update Value, size no change
			dSize++;
	}

	void output(std::ostream& out) const
	{
		for (int i = 0; i < divisor; i++)
			if (table[i].size() == 0)
				out << "NULL" << std::endl;
			else
				out << table[i] << std::endl;
	}

protected:
	sortedChain<K, E>* table;  // hash table
	myHash::hash<K> hash;      // maps type K to nonnegative integer
	int dSize;                 // number of elements in list
	int divisor;               // hash function divisor, namely: table size
};

// overload <<
template <class K, class E>
std::ostream& operator<<(std::ostream& out, const hashChains<K, E>& x)
{
	x.output(out); return out;
}
