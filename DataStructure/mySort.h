#pragma once

// sort methods for array

#include <stdlib.h>
#include <iostream>

using namespace std;

template<typename T>
void bubbleSort(T* head, int size)
{
	if (head == 0 || size <= 1) return;

	for (int i = 0; i < size; ++i)
	{
		bool swapFlag = false;
		for (int j = 0; j < size - 1 - i; ++j) {
			if (head[j] > head[j + 1]) { // ASC
				swapFlag = true;
				T tmp = head[j];
				head[j] = head[j + 1];
				head[j + 1] = tmp;
			}
		}
		if (!swapFlag)
			break;
	}
}

template<typename T>
void insertSort(T* head, int size)
{
	if (head == 0 || size <= 1) return;

	for(int i = 1; i < size; ++i)
	{
		T insert = head[i];
		int j = i - 1;
		for (; j >= 0; --j) {
			if (insert > head[j]) // DSC
				head[j + 1] = head[j];
			else
				break;
		}
		head[j + 1] = insert;
	}
}

template<typename T>
void print(T* p, int size)
{
	for (int i = 0; i < size; ++i)
		cout << p[i] << " ";
	cout << '\n';
}

const int bufSize = 6;
void mySortTest()
{
	int* p = (int*)calloc(bufSize, sizeof(int));
	p[0] = 6;
	p[1] = 5;
	p[2] = 4;
	p[3] = 3;
	p[4] = 2;
	p[5] = 1;

	print(p, bufSize);
	bubbleSort(p, bufSize);
	print(p, bufSize);
	insertSort(p, bufSize);
	print(p, bufSize);

}