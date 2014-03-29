#include "stdafx.h"
#include "../include/String.h"
#include "../include/Type.h"
#include <cstring>

using namespace MPF;

DEFINE_TYPE(String, MPF::String)
std::shared_ptr<String> String::empty = std::make_shared<String>(L"");

String::String() mnoexcept
{
}

String::String(const wchar_t chars[], uint length) mnoexcept
:chars(chars), length(length)
{
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
	return (uint)chars;
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
		auto str = new wchar_t[length + 1];
		wcscpy_s(str, length + 1, chars);

		this->chars = str;
	}
}

String::~String()
{
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
	return this->GetHashCode() == str.GetHashCode();
}

std::shared_ptr<String> String::GetEmpty()
{
	if (!empty)
	{
		empty = std::make_shared<String>(L"");
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
:chars(str.chars), isOwner(str.isOwner), length(str.length)
{
	if (isOwner && chars)
	{
		auto newChars = new wchar_t[length + 1];
		wcscpy_s(newChars, length + 1, str.chars);
		chars = newChars;
	}
}

String::String(String&& str)
:chars(str.chars), isOwner(str.isOwner), length(str.length)
{
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

	if (isOwner && chars)
	{
		auto newChars = new wchar_t[length + 1];
		wcscpy_s(newChars, length + 1, str.chars);
		chars = newChars;
	}
	return *this;
}

const String& String::operator = (String&& str)
{
	Dispose();
	chars = str.chars;
	length = str.length;
	isOwner = str.isOwner;
	str.chars = nullptr;
	str.length = 0;
	str.isOwner = false;

	return *this;
}