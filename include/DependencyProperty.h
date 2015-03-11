#pragma once
#include "Type.h"

NS_MPF

//依赖属性
template<typename TValue>
class DependencyProperty
{
public:
	// 创建 DependencyProperty 的新实例
	DependencyProperty(const String& name)
		:name(name), value()
	{

	}

	// 创建 DependencyProperty 的新实例
	DependencyProperty(String&& name)
		:name(std::move(name)), value()
	{

	}

	// 创建 DependencyProperty 的新实例
	DependencyProperty(const String& name, const TValue& value)
		:name(name), value(value)
	{

	}

	// 创建 DependencyProperty 的新实例
	DependencyProperty(String&& name, const TValue& value)
		:name(std::move(name)), value(value)
	{

	}

	// 创建 DependencyProperty 的新实例
	DependencyProperty(const String& name, TValue&& value)
		:name(name), value(std::forward<TValue>(value))
	{

	}

	// 创建 DependencyProperty 的新实例
	DependencyProperty(String&& name, TValue&& value)
		:name(std::move(name)), value(std::forward<TValue>(value))
	{

	}

	// 获取属性名称
	const String& GetName() const
	{
		return name;
	}

	mgproperty(const String&, Name);

	// 获取值
	const TValue& GetValue() const
	{
		return value;
	}

	// 获取值
	TValue& GetValue()
	{
		return value;
	}
	// 设置值
	void SetValue(TValue&& value)
	{
		this->value = std::forward<TValue>(value);
	}
	// 设置值
	void SetValue(const TValue& value)
	{
		this->value = value;
	}
	mproperty(const TValue&, Value);
private:
	String name;
	TValue value;
};

NS_ED