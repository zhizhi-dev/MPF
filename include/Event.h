#pragma once
#include "Type.h"

NS_MPF

//事件
template<typename TDelegate>
class Event
{
public:
	//创建 Event 的新实例
	Event() mnoexcept
	{

	}

	//添加侦听器
	void operator += (TDelegate handler)
	{
		handlers.push_back(handler);
	}

	//删除侦听器
	void operator -= (TDelegate handler)
	{
		handlers.erase(std::find(handlers.begin(), handlers.end(), handler));
	}

	//激活侦听器
	void operator ()(std::function<void(TDelegate)> func) const
	{
		Invoke(func);
	}
private:
	//激活侦听器
	void Invoke(std::function<void(TDelegate)> func) const
	{
		for (auto& handler : handlers)
		{
			func(handler);
		}
	}

	//侦听器表
	std::vector<TDelegate> handlers;
};

NS_ED