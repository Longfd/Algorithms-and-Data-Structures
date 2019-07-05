#include "minHeap.h"

using namespace std;

void minHeapTest()
{
	try {
		minHeap<int> heap;
		heap.push(1);
		heap.push(2);
		heap.push(3);
		heap.push(4);
		heap.push(5);
		heap.push(6);

		cout << "heap:" << heap;
		heap.sort();
		cout << "heap.sort():" << heap;
		heap.heapify();
		cout << "heap.heapify():" << heap;
		cout << "heap.size:" << heap.size() << endl;

		int a[3] = { 3, 2, 1 };
		minHeap<int> heap2;
		heap2.initialize(a, 3);
		cout << "heap2.size:" << heap2.size() << endl;
		cout << "heap2.front():" << heap2.front() << endl;
		heap2.pop();
		heap2.pop();
		heap2.pop();
		cout << "heap2.size:" << heap2.size() << endl;
		cout << "heap2.front():" << heap2.front() << endl;
	}
	catch (heapEmpty e) {
		cout << e.what();
	}
	catch (exception e) {
		cout << "exception" << e.what();
	}
	catch (...) {
		cout << "UnKown Exception!\n";
	}
}
