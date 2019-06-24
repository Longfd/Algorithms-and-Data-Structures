#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>
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
	bool checkPalindromeList();

	// check palindrome  with array
	bool checkPalindromeList2() const;

	// reverse
	void reverse();

	// delete last n nodes
	void deleteLastN(int num);
	void clear();

	// find middle node
	T& getMiddle() const;

	void sort();
	void merge2Lists(chain<T>& list2);

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
	chainNode<T>* reverse(chainNode<T>* first);
	chainNode<T>* findMiddle() const;

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
bool chain<T>::checkPalindromeList()
{
	// 单个节点为回文
	if (listSize == 1) return true;

	// 两个相同节点为回文
	if (listSize == 2) {
		if(firstNode->element == firstNode->next->element)
			return true;
		else
			return false;
	}

	// 3个或以上
	// 使用快慢指针找中间节点(区分奇偶情况)
	chainNode<T>* mid = findMiddle();

	// 从中点向后逆转链表
	chainNode<T>* end = reverse(mid);
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

// time:O(n), space: O(1)
template<typename T>
chainNode<T>* chain<T>::reverse(chainNode<T>* first)
{
	chainNode<T>* p1 = 0, *p2 = 0, *p3 = 0;

	p1 = first;
	p2 = p1->next;
	if (p2 == nullptr) return p1;

	p3 = p2->next;
	if (p3 == nullptr) {
		p2->next = p1;
		p1->next = 0;
	}
	else {
		p1->next = 0;
		while (p3 != 0) {
			p2->next = p1;
			p1 = p2;
			p2 = p3;
			p3 = p3->next;
		}
		p2->next = p1;
	}

	return p2;
}

template<typename T>
void chain<T>::reverse()
{
	firstNode = reverse(firstNode);
}

template<typename T>
void chain<T>::deleteLastN(int num)
{
	chainNode<T>* prev = 0, * del = 0, * tmp = 0;

	if (num < 0 || num > listSize) {
		std::ostringstream oss;
		oss << "delete last number:" << num << " listSize:" << listSize;
		throw illegalParameterValue(oss.str());
	}

	if (num == listSize) return clear();

	prev = firstNode;
	for (int i = 0; i < listSize - num - 1; ++i)
		prev = prev->next;

	del = prev->next;
	prev->next = 0;
	while (del != 0)
	{
		tmp = del->next;
		delete del;
		del = tmp;
	}

	listSize -= num;
}

template<typename T>
void chain<T>::clear()
{
	chainNode<T>* p;
	while (firstNode != 0)
	{
		p = firstNode->next;
		delete firstNode;
		firstNode = p;
	}

	listSize = 0;
}

template<typename T>
chainNode<T>* chain<T>::findMiddle() const
{
	chainNode<T>* fast, *slow;
	fast = slow = firstNode;

	while (fast->next != 0)
	{
		fast = fast->next;
		slow = slow->next;
		if (fast->next != 0) 
			fast = fast->next;
		else
			break;
	}

	return slow;
}

template<typename T>
T& chain<T>::getMiddle() const
{
	return findMiddle()->element;
}

template<typename T>
void chain<T>::merge2Lists(chain<T>& list2)
{

}

template<typename T>
void chain<T>::sort()
{

}
