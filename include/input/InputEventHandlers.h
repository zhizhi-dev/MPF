#pragma once
#include "../core.h"
#include "MouseEventArgs.h"

NS_MPF
NS_INPUT

//鼠标事件处理器
using MouseEventHandler = std::function<void(MouseEventArgs&)>;

NS_ED
NS_ED