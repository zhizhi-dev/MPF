#pragma once
#include "../core.h"
#include "../visual/Point.h"
#include "MouseButtons.h"
#include "../RoutedEventArgs.h"

NS_MPF
NS_UI
class UIElement;
NS_ED
NS_INPUT

//鼠标事件
class MouseEventArgs : public RoutedEventArgs
{
public:
	MouseEventArgs(MPF::Visual::Point&& position)
		:position(std::move(position))
	{

	}

	//获取相对窗口的坐标
	MPF::Visual::Point GetPosition() const mnoexcept
	{
		return position;
	}

	//获取相对UI元素的坐标
	MPF_API MPF::Visual::Point GetPosition(const MPF::UI::UIElement& element) const mnoexcept;
private:
	//相对窗口的坐标
	MPF::Visual::Point position;
};

NS_ED
NS_ED