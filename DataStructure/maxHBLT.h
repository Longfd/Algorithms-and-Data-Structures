// a max priority tree implemented with height biased leftist tree
// derives from the ADT priorityQueue
// also derives from linkedBinaryTree<std::pair<int, T>>
// first componet of a pair is the s value(内部节点x到外部节点的最短边长, 即以x顶点为根的树的最小高度s, 顶点数至少为2^s - 1) 
// and the second is the data

#pragma once

#include "priorityQueue.h"
#include "linkedBinaryTree.h"
#include "binaryTreeNode.h"
#include "myException.h"
#include <sstream>
#include <utility>

void maxHBLTTest();

template<typename T>
class maxHBLT :public priorityQueue<T>,
	public linkedBinaryTree<std::pair<int, T>>
{
public:
	maxHBLT()
		:priorityQueue<T>(),
		linkedBinaryTree<std::pair<int, T>>()
	{}
	~maxHBLT(){}

	// ADT methods
	bool empty() const override { return this->treeSize == 0; }
	int size() const override { return this->treeSize; }
	const T& front() override 
	{
		if (empty())
			throw queueEmpty();
		return this->root->element.second;
	}
	void push(const T& theElement) override;
	void pop() override;

	// addtional methods
	void initialize(T*, int);
	void output() { this->postorderPrint(); }
	void meld(maxHBLT<T>& theHBLT)
	{// meld *this and theHBLT
		meld(this->root, theHBLT.root);
		this->treeSize += theHBLT.treeSize;
		theHBLT.treeSize = 0;
		theHBLT.root = nullptr;
	}

private:
	void meld(binaryTreeNode<std::pair<int, T>>* &, 
		binaryTreeNode<std::pair<int, T>>* &);
};

template<typename T>
void maxHBLT<T>::meld(binaryTreeNode<std::pair<int, T>>* & x,
	binaryTreeNode<std::pair<int, T>>* & y)
{// Meld leftist trees with roots *x and *y.
 // Return pointer to new root in x.
	if (y == nullptr)
		//throw illegalParameterValue("maxHBLT<T>::meld: y should be not null"); 
		// Notice: if this, the tree never can be cleaned
		return;

	if (x == nullptr) {
		x = y;
		return;
	}

	// x always point to the bigger root
	if (x->element.second < y->element.second)
		std::swap(x, y);

	meld(x->rightChild, y);

	if (x->leftChild == nullptr) // Notice: if left is null, the min s value should be 1
	{// after swap, the S value of x is 1
		std::swap(x->leftChild, x->rightChild);
		x->element.first = 1;
	}
	else if (x->leftChild->element.first < x->rightChild->element.first) 
	{// swap only if left subtree has smaller s value
		std::swap(x->leftChild, x->rightChild);
		x->element.first = x->rightChild->element.first + 1;
	}
}

template<typename T>
void maxHBLT<T>::initialize(T* p, int num)
{// init with meld
	if (num < 1)
		throw illegalParameterValue(" maxHBLT<T>::initialize: num should be >= 1");

	for (int i = 0; i < num; ++i) {
		binaryTreeNode<std::pair<int, T>>* newNode = new binaryTreeNode<std::pair<int, T>>(
			std::make_pair(1, p[i]), 0, 0);
		meld(this->root, newNode);
		++this->treeSize;
	}
}


template<typename T>
void maxHBLT<T>::push(const T& theElement)
{
	binaryTreeNode<std::pair<int, T>>* newNode = new binaryTreeNode<std::pair<int, T>>(
		std::make_pair(1, theElement), 0, 0);
	meld(this->root, newNode);
	++this->treeSize;
}

template<typename T>
void maxHBLT<T>::pop()
{
	if (this->root == NULL)
		throw queueEmpty();

	binaryTreeNode<std::pair<int, T>>* x = this->root->leftChild;
	binaryTreeNode<std::pair<int, T>>* y = this->root->rightChild;
	meld(x, y);

	delete this->root;
	this->root = x;
	this->treeSize--;
}

