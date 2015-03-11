//
// MPF
// 视图状态
//
// (c) SunnyCase 
// 创建日期 2015-03-11
#pragma once
#include "../ui/UIElement.h"

NS_MPF
NS_VSL

// 视图状态
class VisualState
{
public:
	VisualState(const String& name, std::function<const any&(const UI::UIElement&, const String&)> provider)
		:name(name), provider(provider)
	{

	}

	const String& GetName() const noexcept { return name; }
	mgproperty(const String&, Name);

	const any& operator()(const UI::UIElement& element, const String& propertyName) const
	{
		return provider(element, propertyName);
	}
private:
	String name;
	std::function<const any&(const UI::UIElement&, const String&)> provider;
};

// 视图状态组
class VisualStateGroup
{
public:
	VisualStateGroup(const String& name)
		:name(name)
	{

	}

	VisualStateGroup(const String& name, std::initializer_list<VisualState> list)
		:name(name)
	{
		for (auto&& state : list)
			visualStates.emplace(state.Name, state);
	}

	const String& GetName() const noexcept { return name; }
	mgproperty(const String&, Name);

	void Add(VisualState&& state)
	{
		auto name = state.Name;
		visualStates.emplace(std::move(name), std::move(state));
	}

	const VisualState& Get(const String& name) const
	{
		auto it = visualStates.find(name);
		THROW_IF_NOT(it != visualStates.end(), "VisualState not found.");
		return it->second;
	}

	const VisualState& operator[](const String& name) const
	{
		return Get(name);
	}

	MPF_API static const String CommonStates;
private:
	String name;
	std::unordered_map<String, VisualState> visualStates;
};

// 视图状态组集合
class VisualStateGroupCollection
{
public:
	VisualStateGroupCollection()
	{

	}

	VisualStateGroupCollection(std::initializer_list<VisualStateGroup> list)
	{
		for (auto&& group : list)
			visualStateGroups.emplace(group.Name, group);
	}

	void Add(VisualStateGroup&& stateGroup)
	{
		auto name = stateGroup.Name;
		visualStateGroups.emplace(std::move(name), std::move(stateGroup));
	}

	const VisualStateGroup& Get(const String& name) const
	{
		auto it = visualStateGroups.find(name);
		THROW_IF_NOT(it != visualStateGroups.end(), "VisualStateGroup not found.");
		return it->second;
	}

	const VisualState& Get(const String& groupName, const String& stateName) const
	{
		return Get(groupName).Get(stateName);
	}

	const VisualStateGroup& operator[](const String& name) const
	{
		return Get(name);
	}
private:
	std::unordered_map<String, VisualStateGroup> visualStateGroups;
};

struct VisualStateStatus
{
	String groupName;
	String stateName;
};

NS_ED
NS_ED