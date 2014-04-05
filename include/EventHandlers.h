#pragma once
#include "core.h"

NS_MPF

//未捕获异常事件处理器
using UncaughtExceptionEventHandler = std::function<void(bool&)>;
//绘制事件
using PaintEventHandler = std::function<void()>;

NS_ED