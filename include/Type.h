#pragma once
#include "String.h"

NS_MPF

//类型
class Type : public Object
{
public:
	//创建 Type 的新实例
	MPF_API Type(const std::shared_ptr<String> typeName);

	MPF_API bool Equals(const std::shared_ptr<Type> type) const;

	//获取类型
	MPF_API DECLARE_GETTYPE(Type)
private:
	const std::shared_ptr<String> typeName;
	DECLARE_TYPE(Type)
};

NS_ED