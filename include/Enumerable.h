#pragma once
#include "common.h"

NS_MPF

class Enumerable
{
public:
	template<class TContainer, class Func>
	static auto ToVector(const TContainer& container, Func func) 
		-> std::vector<typename std::remove_cv<decltype(func(*container.begin()))>::type>
	{
		std::vector<decltype(func(*container.begin()))> results;

		std::transform(std::begin(container), std::end(container), std::back_inserter(results), func);
		return results;
	}
};

NS_ED