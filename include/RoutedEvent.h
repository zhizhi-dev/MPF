#pragma once
#include "core.h"
#include "RoutedEventArgs.h"

NS_MPF

enum class RoutedEventMode
{
	//管道
	Tunnel,
	//气泡
	Bubble
};

class IRoutedEvent
{
public:
	virtual const String& GetName() const = 0;
	virtual RoutedEventMode GetMode() const mnoexcept = 0;
};

//路由事件
template<typename THandler>
class RoutedEvent : public IRoutedEvent
{
public:
	//创建 RoutedEvent 的新实例
	RoutedEvent(const String& name, RoutedEventMode mode)
		:name(name), mode(mode)
	{

	}

	//创建 RoutedEvent 的新实例
	RoutedEvent(String&& name, RoutedEventMode mode)
		:name(std::move(name)), mode(mode)
	{

	}

	//获取事件名称
	virtual const String& GetName() const
	{
		return name;
	}

	//获取事件模式
	virtual RoutedEventMode GetMode() const mnoexcept
	{
		return mode;
	}
private:
	String name;
	RoutedEventMode mode;
};

typedef std::function<void(RoutedEventArgs&)> RoutedEventHandler;

NS_ED