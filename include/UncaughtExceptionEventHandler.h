#pragma once
#include "Delegate.h"

NS_MPF

//未捕获异常事件代理
class UncaughtExceptionEventHandler : public Delegate
{
public:
	MPF_API UncaughtExceptionEventHandler(std::function<void(bool&)> handler) mnoexcept;

	//调用
	MPF_API void Invoke(bool& isHandled) const;

	//调用
	MPF_API void operator()(bool& isHandled) const;

	//获取类型
	MPF_API DECLARE_GETTYPE(UncaughtExceptionEventHandler)
private:
	std::function<void(bool&)> handler;
	DECLARE_TYPE(UncaughtExceptionEventHandler)
};

NS_ED