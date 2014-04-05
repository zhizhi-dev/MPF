#pragma once

#define NS_MPF namespace MPF {
#define NS_ED }

#define NS_INTERN namespace Internal {

#define NS_VSL namespace Visual {
#define NS_GDI namespace GDI {
#define NS_UI namespace UI {

#ifdef _MSC_VER
#define mnoexcept throw()
#else
#define mnoexcept noexcept
#endif

#define mrestrict __restrict

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <array>
#include <tuple>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <cassert>

#ifdef NDEBUG
#define massert(expr) ((void)0)
#define mmassert(expr, message) ((void)0)
#else
#define massert(expr) (void)( (!!(expr)) || (_wassert(_CRT_WIDE(#expr), _CRT_WIDE(__FILE__), __LINE__), 0) )
#define mmassert(expr, message) (void)( (!!(expr)) || (_wassert(_CRT_WIDE(message), _CRT_WIDE(__FILE__), __LINE__), 0) )
#endif
#define mproperty(T, name) __declspec(property(get = Get##name, put = Set##name)) T name;

namespace std
{
	template<typename T>
	static bool operator!=(const std::weak_ptr<T>& ptr1, const std::weak_ptr<T>& ptr2)
	{
		return ptr1.lock() == ptr2.lock();
	}
}