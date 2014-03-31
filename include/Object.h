#pragma once
#include "core.h"

NS_MPF

class Type;
class String;

#define DECLARE_GETINSTANTTYPE(typeName) virtual const Type& GetInstantType()const mnoexcept{ return typeName ## Type; }
#define DECLARE_GETTYPE(typeName) static const Type& GetType() mnoexcept{ return typeName ## Type; }
#define DECLARE_TYPE(typeName) static Type typeName ## Type;
#define DEFINE_TYPE(typeName, fullName) Type typeName::typeName ## Type(L#fullName);

//MPF 中所有对象的基类
class Object
{
public:
	//创建 Object 的新实例
	MPF_API Object();

	//获取哈希值
	MPF_API virtual uint GetHashCode() const mnoexcept;
	//获取类型
	MPF_API DECLARE_GETTYPE(Object)
	MPF_API DECLARE_GETINSTANTTYPE(Object)
private:
	DECLARE_TYPE(Object)
};

NS_ED