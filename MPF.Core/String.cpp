#include "stdafx.h"
#include "../include/String.h"
#include "../include/Type.h"
#include <cstring>
#include "../include/HashAlgorithms.h"

using namespace MPF;

DEFINE_TYPE(String, MPF::String)
String String::empty;

constexpr String::String() noexcept
{
}

String::String(const wchar_t chars[], uint32_t length) noexcept
: chars(chars), length(length)
{
	massert(chars);
}

uint32_t String::GetLength() const noexcept
{
	return length;
}

const wchar_t* String::GetDataPointer() const noexcept
{
	//chars不能为nullptr
	massert(chars != nullptr);

	return chars;
}

uint32_t String::GetHashCode() const noexcept
{
	massert(chars);
	if (hashCode)
		return hashCode;
	else if (length)
	{
		hashCode = Internal::Hash::BKDRHash(chars);
		return hashCode;
	}
	return 0;
}

String::String(const wchar_t* chars, bool isOwner)
:isOwner(isOwner), length(std::wcslen(chars))
{
	//复制字符串
	if (isOwner)
	{
		this->chars = chars;
	}
	else
	{
		massert(chars);
		auto str = new wchar_t[length + 1];
		wcscpy_s(str, length + 1, chars);

		this->chars = str;
		this->isOwner = true;
	}
}

String::~String() noexcept
{
	Dispose();
}

void String::Dispose() noexcept
{
	if (isOwner && chars)
	{
		delete[] chars;
	}
	isOwner = false;
	chars = nullptr;
}

bool String::operator == (const String& str) const noexcept
{
	massert(chars);
	massert(str.chars);

	if (GetHashCode() != str.GetHashCode())
		return false;
	return std::wcscmp(chars, str.chars) == 0;
}

bool String::operator != (const String& str) const noexcept
{
	return !(*this == str);
}

const String& String::GetEmpty()
{
	if (!empty.chars)
	{
		empty.chars = L"";
	}
	return empty;
}

wchar_t String::operator[](size_t index) const
{
	massert(chars);
	massert(index < length);

	return chars[index];
}

String::String(const String& str)
	:chars(str.chars), isOwner(str.isOwner), length(str.length), hashCode(str.hashCode)
{
	massert(chars);
	if (isOwner)
	{
		auto newChars = new wchar_t[length + 1];
		wcscpy_s(newChars, length + 1, str.chars);
		chars = newChars;
	}
}

String::String(String&& str) noexcept
	:chars(str.chars), isOwner(str.isOwner), length(str.length), hashCode(str.hashCode)
{
	massert(chars);
	str.chars = nullptr;
	str.length = 0;
	str.isOwner = false;
	str.hashCode = 0;
}

const String& String::operator = (const String& str)
{
	Dispose();
	chars = str.chars;
	length = str.length;
	isOwner = str.isOwner;
	hashCode = str.hashCode;

	massert(chars);
	if (isOwner && chars)
	{
		auto newChars = new wchar_t[length + 1];
		wcscpy_s(newChars, length + 1, str.chars);
		chars = newChars;
	}
	return *this;
}

const String& String::operator = (String&& str) noexcept
{
	Dispose();
	chars = str.chars;
	length = str.length;
	isOwner = str.isOwner;
	hashCode = str.hashCode;
	massert(chars);
	str.chars = nullptr;
	str.length = 0;
	str.isOwner = false;
	str.hashCode = 0;

	return *this;
}

bool String::IsEmpty() const noexcept
{
	return length == 0;
}