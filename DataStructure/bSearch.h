#pragma once

// 二分查找的性能: O(logn)
// 局限性: 1.数据要求有序; 2.存储结构只能用数组(随机访问) -> 3.需要连续内存, 故数据量不宜过大

// 二分查找实现
template<typename T>
int bSearchNormal(T* a, int low, int high, int value)
{
	int mid = 0;

	while (low <= high)
	{
		mid = low + ((high - low) >> 1); // 等价于除于2, 位操作效率高于除法
		if (a[mid] == value)
			return mid;
		else if (a[mid] < value)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}

// 二分查找变形1: 查找第一个等于
template<typename T>
int bSearchFirstEqual(T* a, int low, int high, int value)
{
	int mid = 0;

	while (low <= high)
	{
		mid = low + ((high - low) >> 1); // 等价于除于2, 位操作效率高于除法
		if (a[mid] == value) {
			if(mid == 0 || a[mid - 1] != value)
				return mid;
			else
				high = mid - 1;
		}
		else if (a[mid] < value)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}

// 二分查找变形2: 查找最后一个等于
template<typename T>
int bSearchLastEqual(T* a, int low, int high, int value)
{
	int mid = 0;

	while (low <= high)
	{
		mid = low + ((high - low) >> 1); // 等价于除于2, 位操作效率高于除法
		if (a[mid] == value) {
			if (mid == high || a[mid + 1] != value)
				return mid;
			else
				low = mid + 1;
		}
		else if (a[mid] < value)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}

// 二分查找变形3: 查找第一个大于等于
template<typename T>
int bSearchFirstBigOrEqual(T* a, int low, int high, int value)
{
	int mid = 0;

	while (low <= high)
	{
		mid = low + ((high - low) >> 1); // 等价于除于2, 位操作效率高于除法
		if (a[mid] >= value) {
			if (mid == 0 || a[mid - 1] < value)
				return mid;
			else
				high = mid - 1;
		}
		else
			low = mid + 1;
	}
	return -1;
}

// 二分查找变形4: 查找最后一个小于等于
template<typename T>
int bSearchLastSmallOrEqual(T* a, int low, int high, int value)
{
	int mid = 0;

	while (low <= high)
	{
		mid = low + ((high - low) >> 1); // 等价于除于2, 位操作效率高于除法
		if (a[mid] <= value) {
			if (mid == high || a[mid + 1] > value)
				return mid;
			else
				low = mid + 1;
		}
		else
			high = mid - 1;
	}
	return -1;
}

void bSearchTest();
