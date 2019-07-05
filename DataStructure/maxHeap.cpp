#include "maxHeap.h"
#include <exception>

using namespace std;

void maxHeapTest()
{
	try {
		maxHeap<int> heap;
		heap.push(1);
		heap.push(2);
		heap.push(3);
		heap.push(4);
		heap.push(5);
		heap.push(6);

		cout << "heap.size:" << heap.size() << endl;
		cout << "heap.front():" << heap.front() << endl;
		heap.pop();
		cout << "heap.size:" << heap.size() << endl;
		cout << "heap.front():" << heap.front() << endl;
		
		int arraySize = heap.size();
		int* p = new int[arraySize];
		heap.sort(p, arraySize);
		cout << "heap.sort():";
		for (int i = 0; i < arraySize; ++i)
			cout << p[i] << " ";
		cout << endl;
		cout << "heap.front():" << heap.front() << endl;

		cout << "heap.heapify()\n";
		heap.heapify();
		cout << "heap.size:" << heap.size() << endl;
		cout << "heap.front():" << heap.front() << endl;

		maxHeap<int> heap2;
		heap2.initialize(p, arraySize);
		cout << "heap2.size:" << heap.size() << endl;
		cout << "heap2.front():" << heap.front() << endl;
	}
	catch (heapEmpty e) {
		e.what();
	}
	catch (exception e) {
		e.what();
	}
	catch (...) {
		cout << "UnKown Exception!\n";
	}
}
