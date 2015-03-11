//
// MPF
// 视图状态管理器
//
// (c) SunnyCase 
// 创建日期 2015-03-11
#include "stdafx.h"
#include "../stdafx.h"
#include "../../include/visual/VisualStateManager.h"

using namespace MPF;
using namespace MPF::UI;
using namespace MPF::Visual;

MPF_API bool VisualStateManager::GoToState(UIElement& element, const String& groupName, const String& stateName) noexcept
{
	try
	{
		auto& groups = element.GetValue(VisualStateGroupsProperty);
		auto& state = groups.Get(groupName, stateName);
		auto status = element.GetValue(VisualStateStatusProperty);

		status[groupName] = { groupName, stateName };
		element.SetValue(VisualStateStatusProperty, std::move(status));
		return true;
	}
	catch (...)
	{
		return false;
	}
}

MPF_API const any & VisualStateManager::GetStateValue(const String & propertyName, const UI::UIElement & element)
{
	if (propertyName == VisualStateStatusProperty.Name ||
		propertyName == VisualStateGroupsProperty.Name)
		return any::empty;

	auto& statusCol = element.GetValue(VisualStateStatusProperty);
	for (auto& statusPair : statusCol)
	{
		auto& status = statusPair.second;
		auto& state = element.GetValue(VisualStateGroupsProperty).Get(status.groupName, status.stateName);
		auto& value = state(element, propertyName);
		if (!value.isEmpty())
			return value;
	}
	return any::empty;
}
