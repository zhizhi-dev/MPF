#include "stdafx.h"
#include "../include/String.h"
#include "../include/Type.h"
#include <cstring>

using namespace MPF;

DEFINE_TYPE(String, MPF::String)
String String::empty;

String::String() mnoexcept
:chars(L""), length(0)
{
}

String::String(const wchar_t chars[], uint length) mnoexcept
:chars(chars), length(length)
{
	massert(chars);
}

uint String::GetLength() const mnoexcept
{
	return length;
}

const wchar_t* String::GetDataPointer() const mnoexcept
{
	//chars不能为nullptr
	massert(chars != nullptr);

	return chars;
}

uint String::GetHashCode() const mnoexcept
{
	massert(chars);
	return std::hash<std::wstring>()(chars);
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

String::~String()
{
	Dispose();
}

void String::Dispose()
{
	if (isOwner && chars)
	{
		delete[] chars;
	}
	isOwner = false;
	chars = nullptr;
}

bool String::operator == (const String& str) const mnoexcept
{
	return std::wcscmp(chars, str.chars) == 0;
}

bool String::operator != (const String& str) const mnoexcept
{
	return std::wcscmp(chars, str.chars) != 0;
}

const String& String::GetEmpty()
{
	if (!empty.chars)
	{
		empty.chars = L"";
	}
	massert(empty.chars);
	return empty;
}

wchar_t String::operator[](size_t index) const
{
	massert(chars);
	massert(index < length);

	return chars[index];
}

String::String(const String& str)
:chars(str.chars), isOwner(str.isOwner), length(str.length)
{
	if (isOwner && chars)
	{
		auto newChars = new wchar_t[length + 1];
		wcscpy_s(newChars, length + 1, str.chars);
		chars = newChars;
	}
}

String::String(String&& str) mnoexcept
:chars(str.chars), isOwner(str.isOwner), length(str.length)
{
	massert(chars);
	str.chars = nullptr;
	str.length = 0;
	str.isOwner = false;
}

const String& String::operator = (const String& str)
{
	Dispose();
	chars = str.chars;
	length = str.length;
	isOwner = str.isOwner;

	massert(chars);
	if (isOwner && chars)
	{
		auto newChars = new wchar_t[length + 1];
		wcscpy_s(newChars, length + 1, str.chars);
		chars = newChars;
	}
	return *this;
}

const String& String::operator = (String&& str) mnoexcept
{
	Dispose();
	chars = str.chars;
	length = str.length;
	isOwner = str.isOwner;
	massert(chars);
	str.chars = nullptr;
	str.length = 0;
	str.isOwner = false;

	return *this;
}

bool String::IsEmpty() const mnoexcept
{
	return length == 0;
}