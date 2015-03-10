//
// MPF
// 线程池
//
// (c) SunnyCase 
// 创建日期 2015-03-09
#include "stdafx.h"
#include "../stdafx.h"
#include "../../include/threading/ThreadPool.h"

using namespace MPF;
using namespace MPF::Threading;

ThreadPool::ThreadPool(size_t maxThreadCount)
	:maxThreadCount(maxThreadCount)
{

}