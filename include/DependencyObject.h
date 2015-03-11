//
// MPF
// 依赖对象
//
// (c) SunnyCase 
// 创建日期 2014-03-25
#pragma once
#include "Type.h"
#include "any.h"
#include "DependencyProperty.h"
#include "RoutedEvent.h"
#include "RoutedEventArgs.h"
#include "Binding.h"

NS_MPF

// 依赖对象
class DependencyObject
{
public:
	//创建 DependencyObject 的新实例
	DependencyObject() {}
	virtual ~DependencyObject();

	// 获取当前值
	template<typename T>
	T& GetValue(DependencyProperty<T>& property) const
	{
		auto& name = property.Name;
		// 检测本地值
		auto& localValue = GetValueCore(name, localValues);
		if (!localValue.isEmpty())
			return (T&)localValue;
		// 检测默认值
		auto& defaultValue = GetBaseDefaultValue(name);
		if(!defaultValue.isEmpty())
			return (T&)defaultValue;
		// 依赖属性默认值
		return property.Value;
	}

	// 设置本地值
	template<typename T>
	void SetValue(const DependencyProperty<T>& property, T&& value)
	{
		auto& name = property.GetName();
		// 检测本地值
		auto it = localValues.find(name);
		if (it != localValues.end())
		{
			//if ((const T&)(it->second) != value)
			{
				it->second = value;
				OnValueChanged(name);
			}
		}
		else
			localValues.emplace(name, std::forward<T>(value));
	}

	// 设置本地值
	template<typename T>
	void SetValue(const DependencyProperty<T>& property, const T& value)
	{
		auto& name = property.GetName();
		// 检测本地值
		auto it = localValues.find(name);
		if (it != localValues.end())
		{
			if ((const T&)(it->second) != value)
			{
				it->second = value;
				OnValueChanged(name);
			}
		}
		else
			localValues.emplace(name, value);
	}

	// 添加本地事件侦听器
	template<typename THandler, typename TArgs>
	void AddEventHandler(const RoutedEvent<THandler>& ent, std::function<void(TArgs&)> handler)
	{
		localEvents.emplace(ent.GetName(), [=](RoutedEventArgs& args)
		{
			handler(*(TArgs*)(&args));
		});
	}

	// 添加默认事件侦听器
	template<typename THandler, typename TArgs>
	void AddDefaultEventHandler(const RoutedEvent<THandler>& ent, std::function<void(TArgs&)> handler)
	{
		AddDefaultEventHandlerCore(ent.Name, [=](RoutedEventArgs& args)
		{
			handler(*(TArgs*)(&args));
		});
	}
protected:
	template<typename T>
	void SetPropertyChangedHandler(const DependencyProperty<T>& property, std::function<void()> handler)
	{
		observers[property.Name] = handler;
	}

	template<typename T>
	void ClearPropertyChangedHandler(const DependencyProperty<T>& property)
	{
		auto& name = property.GetName();
		auto it = observers.find(name);

		if (it != observers.end())
			observers.erase(it);
	}

	MPF_API void OnValueChanged(const String& name) const;
	MPF_API const any& GetLocalValue(const String& name) const;
protected:
	virtual const any& GetValueCore(const String& name, const std::unordered_map<String, any>& values) const;
	// 获取基类默认值
	virtual const any& GetBaseDefaultValue(const String& name) const;
	// 调用基类默认事件处理器
	virtual void InvokeBaseDefaultEventHandler(const IRoutedEvent& ent, RoutedEventArgs& args) const;
	// 添加默认事件处理器
	virtual void AddDefaultEventHandlerCore(const String& name, RoutedEventHandler&& handler) const;
	// 触发事件
	static void RaiseEvent(DependencyObject& obj, const IRoutedEvent& ent, RoutedEventArgs& args);
private:
	// 属性
	std::unordered_map<String, any> localValues;
	std::unordered_map<String, std::function<void()>> observers;
	// 事件
	std::unordered_multimap<String, RoutedEventHandler> localEvents;
};

#define DECLARE_UI_VALUES \
	static std::unordered_map<String, any> defaultValues;	  \
	static std::unordered_multimap<String, RoutedEventHandler> defaultEvents;\
	static std::unordered_map<String, std::unique_ptr<Binding>> commonStyleBindings;

#define DEFINE_UI_VALUES(CLASS) \
	std::unordered_map<String, any> CLASS::defaultValues; \
	std::unordered_multimap<String, RoutedEventHandler> CLASS::defaultEvents;\
	std::unordered_map<String, std::unique_ptr<Binding>> CLASS::commonStyleBindings;

#define DECLARE_UI_FUNCS \
	virtual const any& GetBaseDefaultValue(const String& name) const; \
	virtual void InvokeBaseDefaultEventHandler(const IRoutedEvent& ent, RoutedEventArgs& args) const; \
	virtual void AddDefaultEventHandlerCore(const String& name, RoutedEventHandler&& handler) const;

#define DEFINE_UI_FUNCS(CLASS, BASE) \
	const any& CLASS::GetBaseDefaultValue(const String& name) const \
	{																\
		auto it = CLASS::defaultValues.find(name); 					\
		if (it != CLASS::defaultValues.end()) 						\
			return it->second;										\
		return BASE::GetBaseDefaultValue(name);						\
	}																\
	void CLASS::InvokeBaseDefaultEventHandler(const IRoutedEvent& ent, RoutedEventArgs& args) const \
	{																							\
		if(!args.Handled)																		\
		{																						\
			auto range = defaultEvents.equal_range(ent.GetName());								\
			if (range.first != range.second)													\
			{																					\
				for (auto it = range.first; it != range.second; ++it)							\
					if (!args.Handled)															\
						it->second(args);														\
			}																					\
			else																				\
				BASE::InvokeBaseDefaultEventHandler(ent, args);									\
		}																						\
	}																					  		\
	void CLASS::AddDefaultEventHandlerCore(const String& name, RoutedEventHandler&& handler) const	\
	{																			 				\
		CLASS::defaultEvents.emplace(name, handler); 							  				\
	}

#define DECLARE_PUB_UI_FUNCS \
	template<typename T>	\
	static void SetDefaultValue(const DependencyProperty<T>& property, const T& value)	\
	{																				\
		defaultValues[property.Name] = value;										\
	}																				\
	template<typename T>	\
	static void SetDefaultValue(const DependencyProperty<T>& property, T&& value)	\
	{																				\
		defaultValues[property.Name] = std::forward<T>(value);						\
	}																				\
	template<typename T>	\
	static void SetCommonStyleBinding(const DependencyProperty<T>& property, std::unique_ptr<Binding>&& binding) \
	{																				\
		auto& name = property.GetName();											\
		auto it = commonStyleBindings.find(name);									\
		if (it != commonStyleBindings.end())										\
		{																			\
			if (it->second.get() != binding.get())									\
			{																		\
				it->second = binding;												\
			}																		\
		}																			\
		else																		\
		{																			\
			commonStyleBindings.emplace(name, std::move(binding));					\
		}																			\
	}

#define DEFINE_COMMON_ROUTEDEVENT(name, TArgs) \
	AddDefaultEventHandler<typename std::function<void(TArgs&)>, TArgs>(name##Event, [&](TArgs& args){On##name(args);});

NS_ED