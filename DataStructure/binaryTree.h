#pragma once

template <typename T> class binaryTreeNode;

template <typename T>
class binaryTree
{
public:
	binaryTree() = default;
	virtual ~binaryTree() = default;

	// ADT methods
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual void preorder(void(*)(binaryTreeNode<T>*)) = 0;
	virtual void inorder(void(*)(binaryTreeNode<T>*)) = 0;
	virtual void postorder(void(*)(binaryTreeNode<T>*)) = 0;
	virtual void breadthFirst(void(*)(binaryTreeNode<T>*)) = 0;
};
