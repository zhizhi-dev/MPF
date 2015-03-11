//
// MPF
// 视图状态管理器
//
// (c) SunnyCase 
// 创建日期 2015-03-11
#pragma once
#include "../ui/UIElement.h"
#include "VisualState.h"

NS_MPF
NS_VSL

// 视图状态管理器
class VisualStateManager final
{
public:
	MPF_API static bool GoToState(UI::UIElement& element, const String& groupName, const String& stateName) noexcept;

	MPF_API static const any& GetStateValue(const String& propertyName, const UI::UIElement& element);
public:
	// 视图状态组
	MPF_API static DependencyProperty<VisualStateGroupCollection> VisualStateGroupsProperty;
	// 当前视图状态
	MPF_API static DependencyProperty<std::unordered_map<String, VisualStateStatus>> VisualStateStatusProperty;
private:
	VisualStateManager();
private:
};

NS_ED
NS_ED