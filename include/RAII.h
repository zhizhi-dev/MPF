#pragma once
#include "common.h"

NS_MPF

class AtFinally
{
public:
	AtFinally(const std::function<void(void)> &functor) 
		: functor(functor) {}
	~AtFinally()
	{
		functor();
	}
private:
	std::function<void(void)> functor;
};

NS_ED