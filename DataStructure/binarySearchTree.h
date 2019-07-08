// a binary search tree implemented with linked binary tree
// implement all methods of dictionary and bsTree

#pragma once

#include "linkedBinaryTree.h"
#include "bsTree.h"

void binarySearchTreeTest();

template<typename K, typename E>
class binarySearchTree : public bsTree<K, E>, public linkedBinaryTree<std::pair<const K, E>>
{
public:
	// methods of dictionary:
	bool empty() const override { return this->treeSize == 0; }

	int size() const override { return this->treeSize; }

	virtual std::pair<const K, E>* find(const K&) const override;

	void erase(const K&)override;

	void insert(const std::pair<const K, E>&)override;

	// additional methods of bsTree
	void ascend() override { this->inorderPrint(); }
};

template<typename K, typename E>
void binarySearchTree<K, E>::insert(const std::pair<const K, E>& el)
{
	binaryTreeNode<std::pair<const K, E>>* p = this->root, * pp = 0;
	while (p != nullptr)
	{
		pp = p;
		if (el.first > p->element.first) // allow exist duplicate Key
			p = p->rightChild;
		else if(el.first < p->element.first)
			p = p->leftChild;
		else {
			p->element.second = el.second;
			return;
		}
	}

	binaryTreeNode<std::pair<const K, E>>* newNode 
		= new binaryTreeNode<std::pair<const K, E>>(el, 0, 0);
	if (this->root == nullptr)
		this->root = newNode;
	else
		if(el.first >= pp->element.first)
			pp->rightChild = newNode;
		else
			pp->leftChild = newNode;
	this->treeSize++;
}

template<typename K, typename E>
std::pair<const K, E>*  binarySearchTree<K, E>::find(const K& theKey) const
{
	binaryTreeNode<std::pair<const K, E>>* p = this->root;
	while (p != nullptr)
	{
		if (theKey > p->element.first)
			p = p->rightChild;
		else if (theKey < p->element.first)
			p = p->leftChild;
		else
			return &p->element;
	}

	return nullptr;
}

template<typename K, typename E>
void binarySearchTree<K, E>::erase(const K& theKey)
{
	binaryTreeNode<std::pair<const K, E>>* p = this->root, *pp = 0;
	// find the node to be erase
	while (p != nullptr && p->element.first != theKey)
	{
		pp = p;
		if (theKey > p->element.first)
			p = p->rightChild;
		else
			p = p->leftChild;
	}
	if (p == nullptr) return; // not found

	// p has two child --> convert to "delete node with one child or leaf node": 
	// largest left node (or smallest right node) 
	if (p->leftChild != nullptr && p->rightChild != nullptr) {
		binaryTreeNode<std::pair<const K, E>>* s = p->leftChild, *ps = 0;
		while (s->rightChild != nullptr) {
			ps = s;
			s = s->rightChild;
		}

		// construct new subtree
		binaryTreeNode<std::pair<const K, E>>* newSubTreeRoot
			= new binaryTreeNode<std::pair<const K, E>>(s->element, p->leftChild, p->rightChild);
		if (p == this->root) // pp == null
			this->root = newSubTreeRoot;
		else
			if (p == pp->leftChild)
				pp->leftChild = newSubTreeRoot;
			else
				pp->rightChild = newSubTreeRoot;
		delete p;

		// convert pointer p and pp
		if (ps == nullptr)
			pp = s;
		else
			pp = ps;
		p = s;
	}

	// p has at most one child
	binaryTreeNode<std::pair<const K, E>>* child = 0;
	if (p->leftChild != nullptr)
		child = p->leftChild;
	else if (p->rightChild != nullptr)
		child = p->rightChild; // p is a leaf node or p has one right child
	
	if (p == this->root)
		this->root = child;
	else
		if (p == pp->leftChild)
			pp->leftChild = child;
		else
			pp->rightChild = child;
	delete p;
	this->treeSize--;
}
