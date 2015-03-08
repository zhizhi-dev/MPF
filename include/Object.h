#pragma once
#include "core.h"

NS_MPF

class Type;
class String;

#define DECLARE_GETINSTANTTYPE(typeName) virtual const Type& GetInstantType()const noexcept{ return typeName ## Type; }
#define DECLARE_GETTYPE(typeName) static const Type& GetType() noexcept{ return typeName ## Type; }
#define DECLARE_TYPE(typeName) static Type typeName ## Type;
#define DEFINE_TYPE(typeName, fullName) Type typeName::typeName ## Type(L#fullName);

//MPF 中所有对象的基类
class Object
{
public:
	//创建 Object 的新实例
	constexpr Object() noexcept {}

	//获取哈希值
	virtual uint32_t GetHashCode() const noexcept { return (uint32_t)this; }
	//获取类型
	MPF_API DECLARE_GETTYPE(Object)
	MPF_API DECLARE_GETINSTANTTYPE(Object)
private:
	DECLARE_TYPE(Object)
};

NS_ED