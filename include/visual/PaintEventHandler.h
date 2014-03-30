#pragma once
#include "../Delegate.h"

NS_MPF

//绘制事件代理
class PaintEventHandler : public Delegate
{
public:
	MPF_API PaintEventHandler(std::function<void()> handler) mnoexcept;

	//调用
	MPF_API void Invoke() const;

	//调用
	MPF_API void operator()() const;

private:
	std::function<void()> handler;
};

NS_ED