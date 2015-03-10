#pragma once

#define NS_MPF namespace MPF {
#define NS_ED }

#define NS_INTERN namespace Internal {

#define NS_VSL namespace Visual {
#define NS_GDI namespace GDI {
#define NS_UI namespace UI {
#define NS_INPUT namespace Input {
#define NS_MEDIA namespace Media {
#define NS_IO namespace IO {
#define NS_THREADING namespace Threading{

#if _MSC_VER < 1900
#define noexcept throw()
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
#include <map>

#ifdef NDEBUG
#define massert(expr) ((void)0)
#define mmassert(expr, message) ((void)0)
#else
#define massert(expr) (void)( (!!(expr)) || (_wassert(_CRT_WIDE(#expr), _CRT_WIDE(__FILE__), __LINE__), 0) )
#define mmassert(expr, message) (void)( (!!(expr)) || (_wassert(_CRT_WIDE(message), _CRT_WIDE(__FILE__), __LINE__), 0) )
#endif
#define mproperty(T, name) __declspec(property(get = Get##name, put = Set##name)) T name;
#define mgproperty(T, name) __declspec(property(get = Get##name)) T name;

namespace std
{
	template<typename T>
	static bool operator!=(const std::weak_ptr<T>& ptr1, const std::weak_ptr<T>& ptr2)
	{
		return ptr1.lock() == ptr2.lock();
	}
}

#define THROW_IF_NOT(expr, message) if(!(expr)) throw std::exception(message);