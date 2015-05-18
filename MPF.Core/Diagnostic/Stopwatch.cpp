//
// MPF
// 计时器
//
// (c) SunnyCase 
// 创建日期 2015-05-18
#include "stdafx.h"
#include "../stdafx.h"
#include "../../include/diagnostic/Stopwatch.h"

using namespace MPF;

Stopwatch::Stopwatch()
	:lastTick(0)
{
	THROW_WIN_IFNOT(QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&freq)));
}

void Stopwatch::Restart()
{
	THROW_WIN_IFNOT(QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&lastTick)));
}

double Stopwatch::Stop()
{
	int64_t nowTick;
	THROW_WIN_IFNOT(QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&nowTick)));
	return static_cast<double>(nowTick - lastTick) / freq;
}