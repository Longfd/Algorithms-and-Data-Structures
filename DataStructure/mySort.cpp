#include "mySort.h"

using namespace std;

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

	insertSort(p, bufSize);
	print(p, bufSize);

	bubbleSort(p, bufSize);
	print(p, bufSize);
	

	//merge_sort(p, 0, 5);
	quickSort(p, 0, 5);

	print(p, bufSize);
}
