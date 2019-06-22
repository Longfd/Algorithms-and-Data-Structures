#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "linearList.h"
#include "exception.h"
#include "chainNode.h"


// Test Method
void chainUnitTest();

template<typename T>
class chain : public linearList<T>
{
public:
	chain();
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

	// check palindrome
	bool checkPalindromeList() const;

	// check palindrome  with array
	bool checkPalindromeList2() const;

	// iterators to start and end of list
	class iterator;
	iterator begin() { return iterator(firstNode); }
	iterator end() { return iterator(); }

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
		iterator(chainNode<T>* node = NULL) 
		{
			this->node = node;
		}

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
	void checkIndex(int index) const;

	chainNode<T>* firstNode;
	int listSize;
};

template<typename T>
chain<T>::chain()
{
	firstNode = NULL;
	listSize = 0;
}

template<typename T>
chain<T>::chain(const chain<T>& list)
{
	listSize = list.listSize;

	// empty
	if (listSize == 0) {
		firstNode = NULL;
		return;
	}

	// non-empty
	chain<T>::iterator it = list.begin();
	chain<T>::iterator end = list.end();
	chainNode<T>* p = firstNode;
	for (; it != end; ++it) {
		p = new chainNode<T>(it->element);
		p = firstNode->next;
	}
}

template<typename T>
chain<T>::~chain()
{
	chainNode<T>* tmp = NULL;
	while (firstNode != NULL) {
		tmp = firstNode->next;
		delete firstNode;
		firstNode = tmp;
	}
}

template<typename T>
void chain<T>::checkIndex(int index) const
{
	if (index < 0 || index >= listSize) {
		std::ostringstream oss;
		oss << "index:" << index << " listSize:" << listSize;
		throw illegalParameterValue(oss.str());
	}
}

//ADT(Abstract Data Type) methods
template<typename T>
bool chain<T>::empty() const
{
	return listSize == 0;
}

template<typename T>
int chain<T>::size() const
{
	return listSize;
}

template<typename T>
T& chain<T>::get(int index) const
{
	checkIndex(index);

	chainNode<T>* p = firstNode;
	for (int i = 0; i < index; ++i)
		p = p->next;

	return p->element;
}

template<typename T>
int chain<T>::indexOf(const T& element) const
{
	int count = 0;
	bool find = false;
	chainNode<T>* p = firstNode;
	
	for (; p != NULL; p = p->next) {
		if (p->element == element)
			return count;
		++count;
	}

	return -1;
}

template<typename T>
void chain<T>::erase(int index)
{
	//单向链表结构删除需要前项节点
	checkIndex(index);
	chainNode<T>* pre = firstNode, * deleteNode = NULL;

	//需要区分两种情况: 由前项, 无前项(首节点)
	if (index == 0) {
		deleteNode = firstNode;
		firstNode = firstNode->next;
	}
	else {
		for (int i = 0; i < index - 1; ++i)
			pre = pre->next;

		deleteNode = pre->next;
		pre->next = pre->next->next;
	}

	--listSize;
	delete deleteNode;
}

template<typename T>
void chain<T>::insert(int index, const T& element)
{
	//条件与get(), erase()不同
	if (index < 0 || index > listSize) {
		std::ostringstream oss;
		oss << "index:" << index << " listSize:" << listSize;
		throw illegalParameterValue(oss.str());
	}

	chainNode<T>* pre = firstNode;
	if (index == 0) {
		firstNode = new chainNode<T>(element, firstNode);
	}
	else {
		for (int i = 0; i < index - 1; ++i)
			pre = pre->next;
		pre->next = new chainNode<T>(element, pre->next);
	}

	++listSize;
}

template<typename T>
void chain<T>::output(std::ostream& out) const
{
	for (chainNode<T>* currentNode = firstNode;
		currentNode != NULL;
		currentNode = currentNode->next)
		std::cout << currentNode->element << " ";
}

// overload <<
template<typename T>
std::ostream& operator<<(std::ostream& out, const chain<T>& list)
{
	list.output(out);
	return out;
}

template<typename T>
bool chain<T>::checkPalindromeList() const
{
	// 单个节点为回文
	if (listSize == 1) return true;

	// 两个相同节点为回文
	if (listSize == 2 &&
		firstNode->element == firstNode->next->element)
		return true;
	else
		return false;

	// 3个或以上
	// 使用快慢指针找中间节点(区分奇偶情况)
	chainNode<T>* fast , *slow, *mid2 = nullptr;
	fast = slow = firstNode;
	while (fast->next != nullptr)
	{
		slow = slow->next;
		fast = fast->next;
		if (fast->next != nullptr) {
			fast = fast->next;
			mid2 = slow->next;
		}
		else {
			mid2 = nullptr; // odd
		}
	}

	// 从中点向后逆转链表
	chainNode<T>* mid = slow;
	chainNode<T>* elem = 0, *prev = 0, *save = 0;
	if (mid2 == nullptr) { // odd
		elem = mid;
		prev = mid->next;
	}
	else { // even
		elem = mid2;
		prev = mid2->next;
		mid2->next = nullptr;
	}
	mid->next = nullptr;

	if (prev == nullptr) // only 3 node, prev = elem->next = null
		save = nullptr;
	else
		save = prev->next;

	while (save!=nullptr) {
		prev->next = elem;
		elem = prev;
		prev = save;
		save = save->next;
	}

	if (prev == nullptr) // only 3 node, prev = elem->next = null
		prev = elem;
	else
		prev->next = elem;

	chainNode<T>* end = prev;
	chainNode<T>* front = firstNode;

	// 头尾同时遍历比较, 检测是否为回文
	bool palindrome = true;
	while ( front != end &&
		front != nullptr &&  
		end != nullptr)
	{
		if (front->element != end->element) {
			palindrome = false;
			break;
		}
		front = front->next;
		end = end->next;
	}

	return palindrome;
}

template<typename T>
bool chain<T>::checkPalindromeList2() const
{
	chainNode<T>* origin, * reverse, * p;
	origin = new chainNode<T>[listSize];
	reverse = new chainNode<T>[listSize];
	p = firstNode;

	for (int i = 0; i < listSize; ++i) {
		origin[i] = *p;
		reverse[listSize - 1 - i] = *p;
		p = p->next;
	}

	bool palindrome = true;
	for (int i = 0; i < listSize; ++i) {
		if (origin[i].element != reverse[i].element) {
			palindrome = false;
			break;
		}
	}
	delete[] origin;
	delete[] reverse;

	return palindrome;
}

