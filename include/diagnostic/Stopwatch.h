//
// MPF
// 计时器
//
// (c) SunnyCase 
// 创建日期 2015-05-18
#pragma once
#include "../core.h"

NS_MPF

///<summary>计时器</summary>
class Stopwatch
{
public:
	MPF_API Stopwatch();

	///<summary>重新开始计时</summary>
	MPF_API void Restart();

	///<summary>停止计时并返回流逝时间（秒）</summary>
	MPF_API double Stop();
private:
	int64_t lastTick, freq;
};

NS_ED