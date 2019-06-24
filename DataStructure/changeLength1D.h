#pragma once

//change the length of an array

#include "myException.h"
#include <algorithm>

template<typename T>
void changeLength1D(T*& p, int oldLength, int newLength)
{
	if (newLength < 0)
		throw illegalParameterValue("new length must be >= 0");

	T* tmp = new T[newLength];
	int num = std::min(oldLength, newLength);
	std::copy(p, p + num, tmp);
	delete[] p;
	p = tmp;
}