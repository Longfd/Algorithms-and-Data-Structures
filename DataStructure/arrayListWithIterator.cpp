#include "arrayListWithIterator.h"


int main()
{
	try
	{
		arrayList<int> list;
		list.insert(0, 1);
		list.insert(0, 2);

		std::cout << list;
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
