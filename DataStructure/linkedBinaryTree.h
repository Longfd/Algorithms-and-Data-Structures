#pragma once

#include <iostream>
#include <utility>
#include "binaryTreeNode.h"
#include "binaryTree.h"
#include "myException.h"
#include "arrayQueue.h"

void linkedBinaryTreeTest();

template<typename T>
class linkedBinaryTree
{
public:
	linkedBinaryTree()
		: root(0), treeSize(0)
	{
	}
	linkedBinaryTree(const T& el, linkedBinaryTree<T>& left, linkedBinaryTree<T>& right)
	{
		root = new binaryTreeNode<T>(el, left.root, right.root);
		treeSize = left.treeSize + right.treeSize + 1;
		left.root = right.root = 0;
		left.treeSize = right.treeSize = 0;
	}
	~linkedBinaryTree() 
	{ 
		visit = deleteElement; 
		postorder(root); 
	}

	bool empty() const { return treeSize == 0; }
	int size() const { return treeSize; }
	const binaryTreeNode<T>* getRoot() { return root; }
	void preorderPrint() { visit = printElement; preorder(root); std::cout << std::endl; }
	void inorderPrint() { visit = printElement; inorder(root); std::cout << std::endl; }
	void postorderPrint() { visit = printElement; postorder(root); std::cout << std::endl; }
	void breadthFirstPrint() { visit = printElement; breadthFirst(root); std::cout << std::endl; }

	// add method
	int height() const;
	int height(const binaryTreeNode<T>* node) const;

protected:
	static void (*visit)(binaryTreeNode<T>*); // visit function

	static void printElement(binaryTreeNode<T>* node) { std::cout << node->element << " "; }
	static void deleteElement(binaryTreeNode<T>* node) { delete node; node = nullptr; }
	void preorder(binaryTreeNode<T>* node);
	void inorder(binaryTreeNode<T>* node);
	void postorder(binaryTreeNode<T>* node);
	void breadthFirst(binaryTreeNode<T>* node);

	binaryTreeNode<T>* root;
	int treeSize;
};
// the following should work but gives an internal compiler error
// template <class E> void (*linkedBinaryTree<E>::visit)(binaryTreeNode<E>*);
// so the explicit declarations that follow are used for our purpose instead
void(*linkedBinaryTree<int>::visit)(binaryTreeNode<int>*);
void(*linkedBinaryTree<char>::visit)(binaryTreeNode<char>*);
void(*linkedBinaryTree<std::pair<int, char> >::visit)(binaryTreeNode<std::pair<int, char> >*);
void(*linkedBinaryTree<std::pair<const int, char> >::visit)(binaryTreeNode<std::pair<const int, char> >*);

template<>
static void linkedBinaryTree<std::pair<int, char>>::printElement(
	binaryTreeNode<std::pair<int, char>>* node) 
{ std::cout << node->element.first << node->element.second << " "; }
template<>
static void linkedBinaryTree<std::pair<const int, char>>::printElement(
	binaryTreeNode<std::pair<const int, char>>* node)
{
	std::cout << node->element.first << node->element.second << " ";
}


template<typename T>
void linkedBinaryTree<T>::preorder(binaryTreeNode<T>* node)
{
	if (node)
	{
		visit(node);
		preorder(node->leftChild);
		preorder(node->rightChild);
	}
}

template<typename T>
void linkedBinaryTree<T>::inorder(binaryTreeNode<T>* node)
{
	if (node)
	{
		inorder(node->leftChild);
		visit(node);
		inorder(node->rightChild);
	}
}

template<typename T>
void linkedBinaryTree<T>::postorder(binaryTreeNode<T>* node)
{
	if (node)
	{
		postorder(node->leftChild);
		postorder(node->rightChild);
		visit(node);
	}
}

template<typename T>
void linkedBinaryTree<T>::breadthFirst(binaryTreeNode<T>* node)
{
	arrayQueue<binaryTreeNode<T>*> que;
	binaryTreeNode<T>* p = root;
	
	if (p != nullptr)
		que.push(root);
	
	while (!que.empty())
	{
		p = que.front();
		que.pop();
		visit(p);

		if(p->leftChild)
			que.push(p->leftChild);
		if (p->rightChild)
			que.push(p->rightChild);
	}
}

template<typename T>
int linkedBinaryTree<T>::height() const
{
	arrayQueue<binaryTreeNode<T>*> que;
	binaryTreeNode<T>* p = root;

	if (p)
		que.push(p);
	else
		throw treeEmpty();

	int heightCount = 1;
	int levelCount = que.size();

	while (!que.empty())
	{
		if (levelCount == 0) {// go to next level
			levelCount = que.size();
			heightCount++;
		}

		p = que.front();
		if(p->leftChild)
			que.push(p->leftChild);
		if (p->rightChild)
			que.push(p->rightChild);

		que.pop();
		levelCount--;
	}

	return heightCount;
}

template<typename T>
int linkedBinaryTree<T>::height(const binaryTreeNode<T>* node) const
{
	if (node == nullptr) return 0;

	int leftHeight = height(node->leftChild);
	int rightHeight = height(node->rightChild);

	return leftHeight > rightHeight ? ++leftHeight : ++rightHeight;
}
