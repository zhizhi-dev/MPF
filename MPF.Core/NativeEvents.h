#pragma once
#include "../include/input/MouseButtons.h"
#include "../include/visual/Point.h"

NS_MPF
NS_INPUT

struct NativeMouseEventArgs
{
	NativeMouseEventArgs(const MPF::Visual::Point& position)
		:Position(position)
	{

	}

	//鼠标相对窗口的位置
	MPF::Visual::Point Position;
};

typedef std::function<void(NativeMouseEventArgs&)> NativeMouseEventHandler;

NS_ED
NS_ED