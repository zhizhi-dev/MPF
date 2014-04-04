#pragma once
#include "../Type.h"
#include "../visual/Quad.h"

NS_MPF
NS_UI

//渲染参数
struct RenderArgs
{
	float ElapsedTime;
};

//更新参数
struct UpdateArgs
{
	MPF::Visual::Point ParentOffset;
	float ElapsedTime;
};

NS_ED
NS_ED