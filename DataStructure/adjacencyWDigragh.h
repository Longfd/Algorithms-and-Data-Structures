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

	int numberOfVertices() const override { return n; }

	int numberOfEdges() const override { return e; }

	bool directed() const override { return true; }

	bool weighted() const override { return true; }

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
			n(number),
			currentVertex(1)
		{}
		~myIterator() {}
		int next() { 
			for (int i = currentVertex; i < n + 1; ++i)
				if (row[i] != noEdge) {
					currentVertex = i + 1;
					return i;
				}
			currentVertex = n + 1;
			return 0;
		}
		int next(T& theWeight) { 
			for (int i = currentVertex; i < n + 1; ++i)
				if (row[i] != noEdge) {
					currentVertex = i + 1;
					theWeight = row[i];
					return i;
				}
			currentVertex = n + 1;
			return 0;
		}

	protected:
		T* row;           // row of adjacency matrix
		T noEdge;         // theRow[i] == noEdge iff no edge to i
		int n;            // number of vertices
		int currentVertex;
	};

	myIterator* iterator(int theVertex) override {
		checkVertex(theVertex);
		return new myIterator(a[theVertex], noEdge, n);
	}
	void output(std::ostream&) const override;

	// addtional method
	void checkVertex(int theVertex) const;
	void bfs(int v, int reach[], int label);
	void dfs(int v, int reach[], int label);

protected:
	int n;           // number of vertices
	int e;           // number of edges
	T ** a;           // adjacency array
	T noEdge;        // denotes absent edge
};

template <class T>
void adjacencyWDigraph<T>::checkVertex(int theVertex) const
{// verify that i is a valid vertex
	if (theVertex < 1 || theVertex > n) {
		std::ostringstream oss;
		oss << "invalid vertex:" << theVertex;
		throw illegalParameterValue(oss.str());
	}
}

template <class T>
bool adjacencyWDigraph<T>::existsEdge(int i, int j) const
{
	checkVertex(i);
	checkVertex(j);
	if (a[i][j] != noEdge)
		return true;
	else
		return false;
}

template <class T>
void adjacencyWDigraph<T>::insertEdge(edge<T>* theEdge)
{
	int v1 = theEdge->vertex1();
	int v2 = theEdge->vertex2();
	if (v1 < 1 || v2 < 1 || v1 > n || v2 > n || v1 == v2) {
		std::ostringstream oss;
		oss << "v1:" << v1 << " v2:" << v2
			<< " is not a permissive edge";
		throw illegalParameterValue(oss.str());
	}

	if (a[v1][v2] == noEdge)
		e++;
	a[v1][v2] = theEdge->weight();
}

template <class T>
void adjacencyWDigraph<T>::eraseEdge(int i, int j)
{
	if (i < 1 || j < 1 || i > n || j > n || a[i][j] == noEdge)
		return;

	a[i][j] = noEdge;
	--e;
}

template <class T>
int adjacencyWDigraph<T>::degree(int theVertex) const
{// degree is used for undirected graph
	throw undefinedMethod("adjacencyWDigraph<T>::degree(int theVertex) undefined!");
}

template <class T>
int adjacencyWDigraph<T>::inDegree(int theVertex) const
{
	checkVertex(theVertex);

	int sum = 0;
	for (int i = 1; i < n + 1; ++i)
		if (a[i][theVertex] != noEdge)
			++sum;
	return sum;
}

template <class T>
int adjacencyWDigraph<T>::outDegree(int theVertex) const
{
	checkVertex(theVertex);

	int sum = 0;
	for (int i = 1; i < n + 1; ++i)
		if (a[theVertex][i] != noEdge)
			++sum;
	return sum;
}

template <class T>
void adjacencyWDigraph<T>::output(std::ostream& out) const
{// output the adjacency matrix
	for (int i = 1; i < n + 1; ++i) {
		std::copy(a[i] + 1, a[i] + n + 1, std::ostream_iterator<T>(out, " "));
		out << std::endl;
	}
}

template <class T>
std::ostream& operator<<(std::ostream& out, const adjacencyWDigraph<T>& aWDigraph) 
{
	aWDigraph.output(out);
	return out;
}

template <class T>
void adjacencyWDigraph<T>::bfs(int v, int reach[], int label)
{// breadth first search, traverse all vertexs that the vertex "v" can reach
	checkVertex(v);

	arrayQueue<T> que;
	que.push(v);
	while (!que.empty())
	{
		int w = que.front();
		que.pop();
		reach[w] = label;

		for (int i = 1; i < n + 1; ++i)
			// push an adjacent vertex that hasn't been reached
			if (a[w][i] != noEdge && reach[i] != label)
				que.push(i);
	}
}

template <class T>
void adjacencyWDigraph<T>::dfs(int v, int reach[], int label)
{// depth first search, traverse all vertexs that the vertex "v" can reach
	reach[v] = label;

	for (int i = 1; i < n + 1; ++i)
		if (a[v][i] != noEdge && reach[i] != label)
			dfs(i, reach, label);
}
