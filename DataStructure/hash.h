#pragma once

// functions to convert from type K to nonnegative integer
// derived from similar class in SGI STL

#include <string>

namespace myHash {
	template <class K> class hash;

	template<>
	class hash<std::string>
	{
	public:
		std::size_t operator()(const std::string theKey) const
		{// convert theKey to a nonnagetive integer
			unsigned long hashValue = 0;
			int length = (int)theKey.length();
			for (int i = 0; i < length; ++i)
				hashValue = 5 * hashValue + theKey.at(i);

			return (std::size_t)hashValue;
		}
	};

	template<>
	class hash<int>
	{
	public:
		std::size_t operator()(const int theKey) const
		{
			return std::size_t(theKey);
		}
	};

	template<>
	class hash<long>
	{
	public:
		std::size_t operator()(const long theKey) const
		{
			return std::size_t(theKey);
		}
	};

};
