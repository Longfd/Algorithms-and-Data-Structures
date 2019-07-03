#pragma once

template<typename T>
class binaryTreeNode
{
public:
	binaryTreeNode()
		:element(),
		leftChild(0),
		rightChild(0)
	{
	}
	binaryTreeNode(const T& el, binaryTreeNode<T>* left, binaryTreeNode<T>* right)
		:element(el),
		leftChild(left),
		rightChild(right)
	{
	}

	T element;
	binaryTreeNode<T>* leftChild;
	binaryTreeNode<T>* rightChild;
};
