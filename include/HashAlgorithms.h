#pragma once
#include "core.h"

NS_MPF
NS_INTERN

namespace Hash
{
	///<summary>BKDR Hash Function</summary>
	///<description>本算法由于在Brian Kernighan与Dennis Ritchie的《The C Programming Language》一书被展示而得
	/// 名，是一种简单快捷的hash算法，也是Java目前采用的字符串的Hash算法（累乘因子为31）。</description>
	template<class T>
	size_t BKDRHash(const T *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * 131 + ch;       
		}
		return hash;
	}
}

NS_ED
NS_ED