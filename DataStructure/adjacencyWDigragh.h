// adjacent matrix representation of a weighted directed graph

#include <iostream>
#include <sstream>
#include <iterator>
#include "graph.h"
#include "weightedEdge.h"
#include "vertexIterator.h"
#include "make2dArray.h"
#include "myException.h"
#include "arrayQueue.h"

#pragma once

void adjacencyWDigraphTest();

template <class T>
class adjacencyWDigraph : public graph<T>
{
public:
	adjacencyWDigraph(int numberOfVertices = 0, T theNoEdge = 0)
		:n(numberOfVertices),
		e(0),
		a(0),
		noEdge(theNoEdge)
	{
		if (numberOfVertices < 0)
			throw illegalParameterValue("number of vertices must be >= 0");
		
		make2dArray(a, numberOfVertices + 1, numberOfVertices + 1);
		for (int i = 1; i < n + 1; i++)
			std::fill(a[i], a[i] + n + 1, noEdge);  // initialize adjacency matrix
	}
	~adjacencyWDigraph() { delete2dArray(a, n + 1); }

	int numberOfVertices() const { return n; }

	int numberOfEdges() const { return e; }

	bool directed() const { return true; }

	bool weighted() const { return true; }

	bool existsEdge(int, int) const override;
	void insertEdge(edge<T>*) override;
	void eraseEdge(int, int) override;
	int degree(int) const override;
	int inDegree(int) const override;
	int outDegree(int) const override;

	class myIterator : public vertexIterator<T>
	{
	public:
		myIterator(T* theRow, T& theNoEdge, int number) 
			:row(theRow),
			noEdge(theNoEdge),
			n(number)
		{}
		~myIterator() {}
		int next() { return 0; }
		int next(T& theWeight) { return 0; }

	protected:
		T* row;           // row of adjacency matrix
		T noEdge;         // theRow[i] == noEdge iff no edge to i
		int n;            // number of vertices
		int currentVertex;
	};

	myIterator* iterator(int theVertex) {
		checkVertex(theVertex);
		return new myIterator(a[theVertex], noEdge, n);
	}
	void output(std::ostream&) const override;

	// addtional method
	void checkVertex(int theVertex) const;

protected:
	int n;           // number of vertices
	int e;           // number of edges
	T ** a;           // adjacency array
	T noEdge;        // denotes absent edge
};

template <class T>
void adjacencyWDigraph<T>::checkVertex(int theVertex) const
{

}

template <class T>
bool adjacencyWDigraph<T>::existsEdge(int, int) const
{
	return true;
}

template <class T>
void adjacencyWDigraph<T>::insertEdge(edge<T>*)
{

}

template <class T>
void adjacencyWDigraph<T>::eraseEdge(int, int)
{

}

template <class T>
int adjacencyWDigraph<T>::degree(int) const
{
	return 0;
}

template <class T>
int adjacencyWDigraph<T>::inDegree(int) const
{
	return 0;
}

template <class T>
int adjacencyWDigraph<T>::outDegree(int) const
{
	return 0;
}

template <class T>
void adjacencyWDigraph<T>::output(std::ostream&) const
{

}
