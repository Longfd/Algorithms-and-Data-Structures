// abstract class graph
// abstract data type specification for graph data structure

#include <iostream>
#include "edge.h"
#include "vertexIterator.h"

#pragma once
template<class T>
class graph
{
public:
	virtual ~graph() {}

	virtual int numberOfVertices() const = 0;
	virtual int numberOfEdges() const = 0;
	virtual bool directed() const = 0;
	virtual bool weighted() const = 0;
	virtual bool existsEdge(int, int) const = 0;
	virtual void insertEdge(edge<T>*) = 0;
	virtual void eraseEdge(int, int) = 0;
	virtual int degree(int) const = 0;
	virtual int inDegree(int) const = 0;
	virtual int outDegree(int) const = 0;
	virtual vertexIterator<T>* iterator(int) = 0;
	virtual void output(std::ostream&) const = 0;
};
