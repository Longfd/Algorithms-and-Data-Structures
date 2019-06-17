#pragma once

#include "linearList.h"
#include "exception.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include <iterator>

template<typename T> 
class arrayList : public linearList<T>
{
public:
	arrayList(int initialCapacity = 10);
	arrayList(const arrayList<T>&);
	~arrayList() { delete[] element; }

	//ADT(Abstract Data Type)
	bool empty() const override { return listSize == 0; }

	int size() const override { return listSize; }

	T& get(int index) const override;

	int indexOf(const T& element) const override;

	void erase(int index) override;

	void insert(int index, const T& element) override;

	void output(std::ostream& out) const override;

	// additional method
	int capacity() const { return arrayLength; }

	// iterator for arrayList
	class iterator
	{

	protected:
	};

protected:
	//若索引无效, 则抛出异常
	void checkIndex(int index) const;
	void changeLength1D(int newLength);

	T* element;			//存储线性表元素的一维数组
	int arrayLength;	//一维数组容量
	int listSize;		//线性表的元素个数
};

template<typename T>
arrayList<T>::arrayList(int initialCapacity)
{
	if (initialCapacity < 1)
	{
		std::ostringstream s;
		s << "Initial Capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
	element = new T[arrayLength];
	listSize = 0;
}

template<typename T>
arrayList<T>::arrayList(const arrayList<T>& list)
{
	arrayLength = list.arrayLength;
	element = new T[arrayLength];
	listSize = list.listSize;
	std::copy(list.element, list.element + listSize, element);
}

template<typename T>
void arrayList<T>::changeLength1D(int newLength)
{
	if (newLength < 0)
		throw illegalParameterValue("newLength must be > 0");

	T* temp = new T[newLength];
	int num = std::min(listSize, newLength);
	std::copy(element, element + num, temp);
	delete [] element;
	element = temp;

	listSize = num;
	arrayLength = newLength;
}

template<typename T>
void arrayList<T>::checkIndex(int index) const
{
	if (index < 0 || index >= listSize) {
		std::ostringstream s;
		s << "invalid index: " << index << " ListSize:" << listSize;
		throw illegalParameterValue(s.str());
	}
}

template<typename T>
T& arrayList<T>::get(int index) const
{
	checkIndex(index);
	return element[index];
}

template<typename T>
int arrayList<T>::indexOf(const T& el) const
{
	//template <class InputIterator, class T>
	//InputIterator find(InputIterator first, InputIterator last, const T & val);
	//Returns an iterator to the first element in the range [first,last) that compares equal to val. 
	//If no such element is found, the function returns last
	int theIndex = (int)(std::find(element, element + listSize, el) - element);

	if (theIndex == listSize)
		return -1;
	else
		return theIndex;
}

template<typename T>
void arrayList<T>::erase(int index)
{
	checkIndex(index);
	//destruct the element to be erased
	//element[index].~T();
	std::copy(element + index + 1, element + listSize, element + index);
	element[--listSize].~T();
}

template<typename T>
void arrayList<T>::insert(int index, const T& el)
{

	//checkIndex(index);  index can be equal to listSize
	if (index < 0 || index > listSize) {
		std::ostringstream s;
		s << "invalid index: " << index << " ListSize:" << listSize;
		throw illegalParameterValue(s.str());
	}

	if (listSize == arrayLength)
		changeLength1D(arrayLength * 2);

	std::copy_backward(element + index, element + listSize, element + listSize + 1);
	element[index] = el;
	++listSize;
}

template<typename T>
void arrayList<T>::output(std::ostream& out) const
{
	//把线性表插入输出流
	copy(element, element + listSize, std::ostream_iterator<T>(out, " "));
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const arrayList<T>& x)
{
	x.output(out);
	return out;
}
