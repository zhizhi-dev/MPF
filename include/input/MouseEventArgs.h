#pragma once
#include "../core.h"
#include "../visual/Point.h"
#include "MouseButtons.h"
#include "../RoutedEventArgs.h"

NS_MPF
NS_INPUT

//鼠标事件
class MouseEventArgs : public RoutedEventArgs
{
public:
	MouseEventArgs(MPF::UI::UIElement* source, MPF::UI::UIElement* destination,
		const MPF::Visual::Point& position)
		:RoutedEventArgs(source, destination), position(position)
	{

	}

	//获取相对窗口的坐标
	MPF::Visual::Point GetPosition() const noexcept
	{
		return position;
	}

	//获取相对UI元素的坐标
	MPF_API MPF::Visual::Point GetPosition(const MPF::UI::UIElement& element) const noexcept;
private:
	//相对窗口的坐标
	MPF::Visual::Point position;
};

NS_ED
NS_ED