#pragma once

#include <iostream>

template<typename T>
class  linearList
{
public:
	//ADT(Abstract Data Type) methods
	virtual ~ linearList() {}

	virtual bool empty() const = 0;

	virtual int size() const = 0;

	virtual T& get(int index) const = 0;

	virtual int indexOf(const T& element) const = 0;

	virtual void erase(int index) = 0;

	virtual void insert(int index, const T& element) = 0;

	virtual void output(std::ostream& out) const = 0;
};
