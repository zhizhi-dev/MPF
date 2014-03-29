#pragma once
#include "Type.h"

NS_MPF

//依赖属性
template<typename TValue>
class DependencyProperty
{
public:
	//创建 DependencyProperty 的新实例
	DependencyProperty(std::shared_ptr<String> name)
		:name(name), value(std::make_shared<TValue>())
	{

	}

	//创建 DependencyProperty 的新实例
	DependencyProperty(std::shared_ptr<String> name, const TValue& value)
		:name(name), value(std::make_shared<TValue>(value))
	{

	}

	//创建 DependencyProperty 的新实例
	DependencyProperty(std::shared_ptr<String> name, TValue&& value)
		:name(name), value(std::make_shared<TValue>(value))
	{

	}

	//创建 DependencyProperty 的新实例
	DependencyProperty(std::shared_ptr<String> name, std::shared_ptr<TValue> value)
		:name(name), value(value)
	{

	}

	//获取属性名称
	std::shared_ptr<String> GetName() const
	{
		return name;
	}

	//获取值
	const TValue& GetValue() const
	{
		return *value;
	}
private:
	std::shared_ptr<String> name;
	std::shared_ptr<TValue> value;
};

NS_ED