#pragma once

// abstract class dictionary
// abastract data type secification for dictionary data structure
// all methods are pure virtual function
// K is key type and E is value type

#include <utility>

template<class K, class E>
class dictionary
{
public:
	virtual ~dictionary() = default;

	virtual bool empty() const = 0;

	virtual int size() const = 0;

	virtual std::pair<const K, E>* find(const K&) const = 0;

	virtual void erase(const K&) = 0;

	virtual void insert(const std::pair<const K, E>&) = 0;
};
