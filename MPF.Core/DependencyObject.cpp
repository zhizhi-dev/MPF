#include "stdafx.h"
#include "../include/DependencyObject.h"

using namespace MPF;

DependencyObject::~DependencyObject()
{
}

MPF_API void DependencyObject::OnValueChanged(const String& name) const
{
	auto it(observers.find(name));
	if (it != observers.end())
		it->second();
}

const any& DependencyObject::GetBaseDefaultValue(const String& name) const
{
	return any::empty;
}

void DependencyObject::InvokeBaseDefaultEventHandler(const IRoutedEvent& ent, RoutedEventArgs& args) const
{
}

void DependencyObject::AddDefaultEventHandlerCore(const String& name, RoutedEventHandler&& handler) const
{
}

void DependencyObject::RaiseEvent(DependencyObject& obj, const IRoutedEvent& ent, RoutedEventArgs& args)
{
	if (!args.Handled)
	{
		auto range = obj.localEvents.equal_range(ent.GetName());
		if (range.first != range.second)
		{
			for (auto it = range.first; it != range.second; ++it)
				if (!args.Handled)
					it->second(args);
		}
		else
			obj.InvokeBaseDefaultEventHandler(ent, args);
	}
}

MPF_API const any& DependencyObject::GetLocalValue(const String& name) const
{
	auto it = localValues.find(name);
	if (it != localValues.end())
		return it->second;
	return any::empty;
}

const any& DependencyObject::GetValueCore(const String& name, const std::unordered_map<String, any>& values) const
{
	auto it = values.find(name);
	if (it != values.end())
		return it->second;
	return any::empty;
}