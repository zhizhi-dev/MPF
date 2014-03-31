#pragma once
#include "String.h"

NS_MPF

//类型
class Type : public Object
{
public:
	//创建 Type 的新实例
	MPF_API Type(const String& typeName);

	MPF_API bool Equals(const Type& type) const;
	bool operator==(const Type& type) const
	{
		return Equals(type);
	}

	//获取类型
	MPF_API DECLARE_GETTYPE(Type)
private:
	String typeName;
	DECLARE_TYPE(Type)
};

NS_ED