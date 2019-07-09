// abstract class for graph vertex iterator

#pragma once

template<class T>
class vertexIterator
{
public:
	virtual ~vertexIterator() {}
	virtual int next() = 0;
	virtual int next(T&) = 0;
};
