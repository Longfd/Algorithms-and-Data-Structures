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
#include "arrayStack.h"
#include "chainWithIterator.h"

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
	int* rFindPath(int src, int dest); // recursion -> dfs
	bool rPath(int v);
	int* FindShortestPath(int src, int dest); // non-recursion -> bfs

	bool topologicalOrder(int* theOrder);
	void shortestPaths(int source, T* distanceFromSource, int* predecessor);

protected:
	int n;           // number of vertices
	int e;           // number of edges
	T ** a;           // adjacency array
	T noEdge;        // denotes absent edge

	// for find path
	int length = 0;
	int destnation = 0;
	int* path = 0;
	int* reach = 0;
	int* prev = 0;
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
{// no loop
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

template <class T>
int* adjacencyWDigraph<T>::rFindPath(int src, int dest)
{
	checkVertex(src);
	checkVertex(dest);
	length = 0;
	destnation = dest;
	path = (int*)calloc(sizeof(int), n + 1); // record vertex from src to dest, 
											// path[0] = edge number from src to dest 
	reach = (int*)calloc(sizeof(int), n + 1);// lable visited vertex
	if (path == 0 || reach == 0)
		throw std::exception("adjacencyWDigraph<T>::findPath(): path == 0 || reach == 0");

	if (src == dest || rPath(src)) {
		path[0] = length;
	}
	else {
		delete[] path;
		path = nullptr;
	}

	delete[] reach;
	return path;
}

template <class T>
bool adjacencyWDigraph<T>::rPath(int v)
{
	reach[v] = 1;

	for (int u = 1; u < n + 1; ++u) {
		if (a[v][u] == noEdge || reach[u] == 1)
			continue;
		
		path[++length] = u;
		if (u == destnation || rPath(u))
			return true;
		else
			--length;
	}
	return false;
}

template <class T>
int* adjacencyWDigraph<T>::FindShortestPath(int src, int dest)
{
	if (src == dest) return nullptr;
	checkVertex(src);
	checkVertex(dest);

	prev = new int[n + 1];
	reach = new int[n + 1];
	memset(prev, 0, sizeof(int)*(n + 1));
	memset(reach, 0, sizeof(int)*(n + 1));
	arrayQueue<int> que;

	reach[src] = 1;
	que.push(src);
	while (!que.empty())
	{
		int cur = que.front();
		que.pop();

		for (int i = 1; i < n + 1; ++i) {
			if (a[cur][i] == noEdge || reach[i] == 1)
				continue;
			prev[i] = cur;
			if (i == dest) {
				delete[] reach;
				return prev;
			}
			reach[i] = 1; // make sure vertex only vist once 
						  // and prev[] is the shortest path vertex
			que.push(i);
		}
	}

	delete[] reach;
	delete[] prev;
	return nullptr;
}

template <class T>
bool adjacencyWDigraph<T>::topologicalOrder(int* theOrder)
{// Return false if the digraph has no topological order
 // theOrder[0:n-1] is set to a topological order when such an order exist
	
	arrayStack<int> stack;
	int n = numberOfVertices();
	int* inDegree = (int*)calloc(n + 1, sizeof(int));

	// compute in-degree
	for (int i = 1; i <= n; i++) 
		inDegree[i] = this->inDegree(i);

	// the queue contains vertex which in-degree is 0
	for (int i = 1; i <= n; i++)
		if (inDegree[i] == 0)
			stack.push(i);

	// generate topological order
	int j = 0; // cursor for array: theOrder
	while (!stack.empty())
	{
		int theVertex = stack.top();
		stack.pop();
		theOrder[j++] = theVertex;

		for (int i = 1; i <= n; i++) {
			if (a[theVertex][i] != noEdge) {
				inDegree[i]--;
				if (inDegree[i] == 0)
					stack.push(i);
			}
		}
	}

	free(inDegree);
	return (j == n);
}

template <class T>
void adjacencyWDigraph<T>::shortestPaths(int source, T* distanceFromSource, int* predecessor)
{// Find shortest paths to all reachable vertex from Vertex source 
 // Return shortest distances in distanceFromSource
 // Return predecessor information in predecessor
	checkVertex(source);

	chain<int> newReachableVertices;

	// initialize
	for (int i = 1; i <= n; i++) {
		distanceFromSource[i] = a[source][i];
		if (distanceFromSource[i] == noEdge)
			predecessor[i] = -1;
		else {
			predecessor[i] = source;
			newReachableVertices.insert(0, i);
		}
	}
	distanceFromSource[source] = 0;
	predecessor[source] = 0; // source vertex has no predecessor

	// Update distanceFromSource AND predecessor
	while (!newReachableVertices.empty())
	{
		int minDistanceIdx = 0,
			nextVertex = newReachableVertices.get(0),
			minDistance = distanceFromSource[nextVertex];
		for (int i = 0; i < newReachableVertices.size(); i++)
		{
			nextVertex = newReachableVertices.get(i);
			if (distanceFromSource[nextVertex] < minDistance) {
				minDistance = distanceFromSource[nextVertex];
				minDistanceIdx = i;
			}
		}
		nextVertex = newReachableVertices.get(minDistanceIdx);

		// next shortest path is from source to nextVertex
		// delete idx of nextVertex from newReachableVertices and update distanceFromSource
		newReachableVertices.erase(minDistanceIdx);

		for (int j = 1; j <= n; j++)
		{
			if (a[nextVertex][j] != noEdge &&
				(predecessor[j] == -1 ||
					distanceFromSource[j] > distanceFromSource[nextVertex] + a[nextVertex][j]))
			{
				// update distanceFromSource
				distanceFromSource[j] = distanceFromSource[nextVertex] + a[nextVertex][j];
				// not reached before, add j to newReachableVertices
				if (predecessor[j] == -1)
					newReachableVertices.insert(0, j);
				// this line cannot move up
				predecessor[j] = nextVertex;
			}
		}
	}
}
