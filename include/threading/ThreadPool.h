//
// MPF
// 线程池
//
// (c) SunnyCase 
// 创建日期 2015-03-09
#pragma once
#include "Thread.h"

NS_MPF
NS_THREADING

// 线程池
class ThreadPool final
{
public:
	///<summary>创建线程池</summary>
	///<param name="maxThreadCount">最大线程数</param>
	MPF_API ThreadPool(size_t maxThreadCount);
private:
	ThreadPool(const ThreadPool&) = delete;
	ThreadPool& operator=(const ThreadPool&) = delete;
private:
	const size_t maxThreadCount;
};

NS_ED
NS_ED