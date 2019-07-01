#include "bSearch.h"
#include <iostream>

void bSearchTest()
{
	int a1[] = { 0 };
	int a4[] = { 0, 1, 1, 2, 6 };
	int a5[] = { 1, 1, 1, 2, 6, 8};

	// 二分查找
	std::cout << "bSearch(a1:0):" << bSearchNormal(a1, 0, 0, 0) << '\n';
	std::cout << "bSearch(a1:1):" << bSearchNormal(a1, 0, 0, 1) << '\n';

	std::cout << "bSearchFirstEqual(a4:1):" << bSearchFirstEqual(a4, 0, 4, 1) << '\n';
	std::cout << "bSearchLastEqual(a4:1):" << bSearchLastEqual(a4, 0, 4, 1) << '\n';
	std::cout << "bSearchFirstEqual(a4:3):" << bSearchFirstEqual(a4, 0, 4, 3) << '\n';
	std::cout << "bSearchLastEqual(a4:3):" << bSearchLastEqual(a4, 0, 4, 3) << '\n';
	std::cout << "bSearchFirstBigOrEqual(a5:5):" << bSearchFirstBigOrEqual(a5, 0, 5, 5) << '\n';
	std::cout << "bSearchFirstBigOrEqual(a5:9):" << bSearchFirstBigOrEqual(a5, 0, 5, 9) << '\n';
	std::cout << "bSearchLastSmallOrEqual(a5:5):" << bSearchLastSmallOrEqual(a5, 0, 5, 5) << '\n';
	std::cout << "bSearchLastSmallOrEqual(a5:6):" << bSearchLastSmallOrEqual(a5, 0, 5, 6) << '\n';
	std::cout << "bSearchLastSmallOrEqual(a5:0):" << bSearchLastSmallOrEqual(a5, 0, 5, 0) << '\n';

}
