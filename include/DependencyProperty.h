#pragma once
#include "Type.h"

NS_MPF

//依赖属性
template<typename TValue>
class DependencyProperty
{
public:
	//创建 DependencyProperty 的新实例
	DependencyProperty(const String& name)
		:name(name), value()
	{

	}

	//创建 DependencyProperty 的新实例
	DependencyProperty(const String& name, const TValue& value)
		:name(name), value(value)
	{

	}

	//创建 DependencyProperty 的新实例
	DependencyProperty(const String& name, TValue&& value)
		:name(name), value(value)
	{

	}

	//获取属性名称
	const String& GetName() const
	{
		return name;
	}

	//获取值
	const TValue& GetValue() const
	{
		return value;
	}

	//获取值
	TValue& GetValue()
	{
		return value;
	}

	//设置值
	void SetValue(const TValue& value)
	{
		this->value = value;
	}
private:
	String name;
	TValue value;
};

NS_ED