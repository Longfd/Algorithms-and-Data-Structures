#include "arrayListWithIterator.h"


int main()
{
	try
	{
		arrayList<int> list;
		list.insert(0, 1);
		list.insert(0, 2);
		list.insert(0, 3);
		list.insert(0, 4);
		list.insert(0, 5);
		list.insert(0, 6);

		//std::cout << list;

		arrayList<int>::iterator it;
		arrayList<int>::iterator begin = list.begin();
		arrayList<int>::iterator end = list.end();

		//Output using forward iterator
		for (it = begin; it != end; ++it)
			std::cout << *it << " ";
		std::cout << std::endl;

		//Output using backward iterator
		for (it = end; it != begin; )
			std::cout << *--it << " ";
		std::cout << std::endl;
	}
	catch (const std::exception& e) {
		std::cout << "std::exception:" << e.what();
	}
	catch (illegalParameterValue& e) {
		std::cout << "illegalParameterValue:" << e.what();
	}

	getchar();

	return 0;
}
