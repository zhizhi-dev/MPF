#pragma once
#include "core.h"

NS_MPF

class Type;
class String;

#define DECLARE_GETINSTANTTYPE(typeName) virtual std::shared_ptr<Type> GetInstantType()const mnoexcept{ return typeName ## Type; }
#define DECLARE_GETTYPE(typeName) static std::shared_ptr<Type> GetType() mnoexcept{ return typeName ## Type; }
#define DECLARE_TYPE(typeName) static std::shared_ptr<Type> typeName ## Type;
#define DEFINE_TYPE(typeName, fullName) std::shared_ptr<Type> typeName::typeName ## Type = std::make_shared<Type>(Type(std::make_shared<String>(L#fullName)));

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