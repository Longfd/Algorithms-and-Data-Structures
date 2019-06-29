#pragma once

// sort methods for array

#include <stdlib.h>
#include <iostream>

using namespace std;

void mySortTest();

template<typename T>
void bubbleSort(T* head, int size)
{
	if (head == 0 || size <= 1) return;

	for (int i = 0; i < size; ++i)
	{
		bool swapFlag = false;
		for (int j = 0; j < size - 1 - i; ++j) {
			if (head[j] < head[j + 1]) { // DSC
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
			if (insert < head[j]) // ASC
				head[j + 1] = head[j];
			else
				break;
		}
		head[j + 1] = insert;
	}
}


/*
	merge sort

	iterative expression: 
		f(p, q, r) {
			if(q >= r) return;
			mid = r-q / 2;
			f(p, q, mid);
			f(p, mid+1, r);
			merge(p, q, mid, r);
		}

	space complexity: O(n)

	time complexity: t(n) = 2*t(n/2) + n;	t(n/2) = 2*t(n/2^2) + n ... t(1) = C;
						  = 2^2 * t(n/2^2) + 2*n ...
						  = 2^k * t(n/2^k) + k*n
						  = C + nlog2(n)
						  = O(nlogn)
	stability: true;
*/
template<typename T>
void merge(T*p, int start, int mid, int end)
{
	const int size = end - start + 1;
	int leftStart = start;
	int leftEnd = mid;
	int rightStart = mid + 1;
	int rightEnd = end;
	T* tmp = new T[size];
	int tmpStart = 0;

	while (leftStart <= leftEnd &&
		rightStart <= rightEnd)
	{
		if (p[leftStart] <= p[rightStart])
			tmp[tmpStart++] = p[leftStart++];
		else
			tmp[tmpStart++] = p[rightStart++];
	}

	while (leftStart <= leftEnd)
		tmp[tmpStart++] = p[leftStart++];
	while (rightStart <= rightEnd)
		tmp[tmpStart++] = p[rightStart++];

	std::copy(tmp, tmp + size, p + start);
	delete[] tmp;
}

template<typename T>
void merge_sort(T*p, int start, int end)
{
	if (start >= end) return;

	int mid = (end + start) / 2;
	merge_sort(p, start, mid);
	merge_sort(p, mid + 1, end);
	merge(p, start, mid, end);
}

/*
	quick_sort

	iterative expression:
		f(p, q, r) {
			if(q >= r) return;

			s = partition(p, q, r);
			f(p, q, s);
			f(p, s+1, r);
		}

	space complexity: O(1)

	time complexity: best = average = O(nlogn), worst = O(n^2)
*/
const int Cutoff = 3;

template<typename T>
const T& Median3(T* p, int left, int right)
{
	int center = (left + right) / 2;

	if(p[left] > p[center])
		std::swap(p[left], p[center]);

	if (p[left] > p[right])
		std::swap(p[left], p[right]);

	if (p[center] > p[right])
		std::swap(p[center], p[right]);

	// Invariant: p[left] <= p[center] <= &p[right]
	std::swap(p[center], p[right-1]); //
	return p[right - 1];
}

template<typename T>
void quickSort(T*p, int left, int right)
{
	if (right - left + 1 < Cutoff)
		return insertSort(p + left, right - left + 1);
	
	const T& pivot = Median3(p, left, right);
	int i = left + 1, j = right - 2;
	while (1)
	{
		for (; p[i] < pivot; ++i) {} // stop when p[i] >= pivot
		for (; p[j] > pivot; --j) {} // stop when p[j] <= pivot
		if (i < j)
			std::swap(p[i], p[j]);
		else
			break;
	}
	std::swap(p[i], p[right - 1]);

	quickSort(p, left, i - 1);
	quickSort(p, i + 1, right);
}
