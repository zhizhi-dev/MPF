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

		virtual std::unique_ptr<placeholder> clone() const = 0;
	};

	template<typename T>
	class holder : public placeholder
	{
	public:
		holder(T&& value)
			:value(std::forward<T>(value))
		{

		}

		holder(const T& value)
			:value(value)
		{

		}

		virtual std::unique_ptr<placeholder> clone() const
		{
			return std::make_unique<holder<T>>(value);
		}
	private:
		friend class any;
		T value;
	};

	any()
	{

	}

	any(const any& _any)
	{
		if (_any.value)
		{
			value = _any.value->clone();
		}
	}

	any(any&& _any) mnoexcept
	{
		if (_any.value)
		{
			value = std::move(_any.value);
		}
	}

	template<typename T>
	any(const T& value)
		: value(std::make_unique<holder<std::remove_reference_t<std::remove_cv_t<T>>>>(value))
	{

	}

	template<typename T>
	any(T&& value)
		: value(std::make_unique<holder<std::remove_reference_t<std::remove_cv_t<T>>>>(
		std::forward<std::remove_cv_t<T>>(value)))
	{

	}

	template<typename T>
	auto get() const->const std::remove_reference_t<std::remove_cv_t<T>>&
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
			reinterpret_cast<holder<std::remove_reference_t<std::remove_cv_t<T>>>*>(
				this->value.get())->value = value;
		}
		else
		{
			this->value = std::make_unique<holder<std::remove_reference_t<std::remove_cv_t<T>>>>(value);
		}
	}

	template<typename T>
	void set(T&& value)
	{
		if (this->value != nullptr)
		{
			reinterpret_cast<holder<std::remove_reference_t<std::remove_cv_t<T>>>*>(
				this->value.get())->value = std::forward<T>(value);
		}
		else
		{
			this->value = std::make_unique<holder<std::remove_reference_t<std::remove_cv_t<T>>>>(
				std::forward<T>(value));
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

	template<typename T>
	void operator= (T&& value)
	{
		set(std::forward<T>(value));
	}

	bool isEmpty() const mnoexcept
	{
		return value == nullptr;
	}

	static any empty;
private:
	std::unique_ptr<placeholder> value;
};

NS_ED