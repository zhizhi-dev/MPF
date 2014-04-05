#include "stdafx.h"
#include "../include/DependencyObject.h"

using namespace MPF;

DependencyObject::~DependencyObject()
{
	localValues.clear();
	animationValues.clear();
	styleValues.clear();
}

void DependencyObject::OnValueChange(const String& name) const
{
	auto it(observers.find(name));
	if (it != observers.end())
	{
		it->second();
	}
}

any& DependencyObject::FindParentCommonValue(const String& name) const
{
	return any::empty;
}

void DependencyObject::InvokeParentCommonEventHandlers(const IRoutedEvent& ent, RoutedEventArgs& args) const
{
}

void DependencyObject::AddCommonEventHandlers(const String& name, RoutedEventHandler&& handler) const
{
}

void DependencyObject::OnRaiseEvent(const IRoutedEvent& ent, RoutedEventArgs& args)
{
	auto it = localEvents.find(ent.GetName());
	if (it != localEvents.end())
	{
		auto handler = (RoutedEventHandler&)it->second;
		handler(args);
	}
	InvokeParentCommonEventHandlers(ent, args);
}