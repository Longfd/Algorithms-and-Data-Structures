#pragma once

template <typename T>
class chainNode
{
public:
	// methods
	chainNode() : element(), next(0)
	{
	}

	chainNode(const T& elment, chainNode<T>* next = 0) : 
		element(elment), next(next)
	{
	}

	// data members
	T element;
	chainNode<T>* next;
};