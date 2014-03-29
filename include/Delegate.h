#pragma once
#include "Type.h"

NS_MPF

//委托
class Delegate : public Object
{
public:
	//创建 Delegate 的新实例
	MPF_API Delegate() mnoexcept;

	//获取类型
	MPF_API DECLARE_GETTYPE(Delegate)
private:
	DECLARE_TYPE(Delegate)
};

NS_ED