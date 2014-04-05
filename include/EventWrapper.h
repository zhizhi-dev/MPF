#pragma once
#include "core.h"
#include "RoutedEvent.h"

NS_MPF

//事件包装
template<typename TObject, typename THandler, typename TArgs>
class EventWrapper
{
public:
	EventWrapper() mnoexcept{}

	//添加侦听器
	void operator += (THandler handler)
	{
		massert(object);
		massert(ent);
		object->TObject::AddEventHandler(*ent, handler);
	}

	//删除侦听器
	void operator -= (THandler handler)
	{
	}

	//激活侦听器
	void operator ()(TArgs& args) const
	{
		massert(object);
		massert(ent);
		object->TObject::RaiseEvent(*ent, args);
	}

	TObject* object = nullptr;
	RoutedEvent<THandler>* ent = nullptr;
};

#define DEFINE_ROUTED_EVENTWRAPPER(name, CLASS) \
	name.object = this;					 \
	name.ent = &(name##Event);

NS_ED