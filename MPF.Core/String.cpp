#include "stdafx.h"
#include "../include/String.h"
#include "../include/Type.h"
#include <cstring>
#include "../include/HashAlgorithms.h"

using namespace MPF;

DEFINE_TYPE(String, MPF::String)
String String::empty;

constexpr String::String() noexcept
	:needDelete(false)
{
}

String::String(const wchar_t chars[], size_t length)
	: chars(nullptr), length(length), needDelete(true)
{
	massert(chars);
	auto str = new wchar_t[length + 1];
	wcscpy_s(str, length + 1, chars);
	this->chars = str;
}

String::String(const wchar_t* chars)
	: String(chars, std::wcslen(chars))
{
}

size_t String::GetLength() const noexcept
{
	return length;
}

const wchar_t* String::GetDataPointer() const noexcept
{
	//chars²»ÄÜÎªnullptr
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

String::~String() noexcept
{
	Dispose();
}

void String::Dispose() noexcept
{
	if (needDelete && chars)
		delete[] chars;
	needDelete = false;
	chars = nullptr;
	length = 0;
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
	:chars(str.chars), needDelete(str.needDelete), length(str.length), hashCode(str.hashCode)
{
	massert(chars);
	if (needDelete)
	{
		auto newChars = new wchar_t[length + 1];
		wcscpy_s(newChars, length + 1, str.chars);
		chars = newChars;
	}
}

String::String(String&& str) noexcept
	:chars(str.chars), needDelete(str.needDelete), length(str.length), hashCode(str.hashCode)
{
	massert(chars);
	str.chars = nullptr;
	str.length = 0;
	str.needDelete = false;
	str.hashCode = 0;
}

const String& String::operator = (const String& str)
{
	Dispose();
	chars = str.chars;
	length = str.length;
	needDelete = str.needDelete;
	hashCode = str.hashCode;

	massert(chars);
	if (needDelete)
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
	needDelete = str.needDelete;
	hashCode = str.hashCode;
	massert(chars);
	str.chars = nullptr;
	str.length = 0;
	str.needDelete = false;
	str.hashCode = 0;

	return *this;
}

bool String::IsEmpty() const noexcept
{
	return length == 0;
}