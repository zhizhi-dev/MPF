#pragma once
#include "core.h"

NS_MPF

class any
{
public:
	class placeholder
	{
	public:
		virtual ~placeholder()
		{

		}
	};

	template<typename T>
	class holder : public placeholder
	{
	public:
		holder(const T& value)
			:value(value)
		{

		}

		holder(T&& value)
			:value(value)
		{

		}
	private:
		friend class any;
		T value;
	};

	any()
	{

	}

	template<typename T>
	any(const T& value)
		:value(std::make_unique<holder<T>>(value))
	{

	}

	template<typename T>
	any(T&& value)
		: value(std::make_unique<holder<T>>(value))
	{

	}

	template<typename T>
	const T& get() const
	{
		return reinterpret_cast<holder<T>*>(value.get())->value;
	}

	template<typename T>
	T& get()
	{
		return reinterpret_cast<holder<T>*>(value.get())->value;
	}

	template<typename T>
	void set(const T& value)
	{
		if (this->value != nullptr)
		{
			reinterpret_cast<holder<T>*>(this->value.get())->value = value;
		}
		else
		{
			this->value = std::make_unique<holder<T>>(value);
		}
	}

	template<typename T>
	operator const T&() const
	{
		return get<T>();
	}

	template<typename T>
	operator T&()
	{
		return get<T>();
	}

	template<typename T>
	void operator= (const T& value)
	{
		set(value);
	}

	bool empty() const mnoexcept
	{
		return value == nullptr;
	}
private:
	std::unique_ptr<placeholder> value;
};

NS_ED