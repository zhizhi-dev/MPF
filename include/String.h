#pragma once
#include "Object.h"

NS_MPF

class Type;

class String : public Object
{
public:
	//创建空的 String
	MPF_API String() mnoexcept;
	//释放资源
	MPF_API virtual ~String();

	//从字符指针创建 String
	MPF_API String(const wchar_t* chars, bool isOwner = false);

	//从字面量和长度创建 String
	MPF_API String(const wchar_t chars[], uint length) mnoexcept;

	MPF_API String(const String& str);
	MPF_API String(String&& str);

	//从字面量创建 String
	template<uint N>
	String(const wchar_t(&chars)[N]) mnoexcept
		:chars(chars), length(N)
	{

	}

	//获取长度
	MPF_API uint GetLength() const mnoexcept;
	
	//获取数组指针
	MPF_API const wchar_t* GetDataPointer() const mnoexcept;

	//获取哈希值
	MPF_API virtual uint GetHashCode() const mnoexcept;

	//测试相等
	MPF_API bool operator==(const String& str) const mnoexcept;
	//测试不相等
	MPF_API bool operator!=(const String& str) const mnoexcept;

	MPF_API wchar_t operator[](size_t index) const;

	MPF_API const String& operator=(const String& str);
	MPF_API const String& operator=(String&& str) mnoexcept;

	MPF_API bool IsEmpty() const mnoexcept;

	//获取空字符串
	MPF_API static const String& GetEmpty();

	//获取类型
	MPF_API DECLARE_GETTYPE(String)
private:
	void Dispose() mnoexcept;
private:
	static String empty;

	DECLARE_TYPE(String)
	const wchar_t* chars = L"";
	bool isOwner = false;
	uint length = 0;
};

NS_ED

namespace std
{
	template<>
	class hash<MPF::String>
	{
	public:
		size_t operator()(const MPF::String& str) const
		{
			return str.GetHashCode();
		}
	};
}