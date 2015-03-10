//
// MPF
// 二进制读取器
//
// (c) SunnyCase 
// 创建日期 2015-03-10
#pragma once
#include "Stream.h"

NS_MPF
NS_IO

// 二进制读取器
class BinaryReader final
{
public:
	BinaryReader(std::shared_ptr<Stream> stream)
		:stream_holder(stream), stream(*stream)
	{

	}

	BinaryReader(Stream& stream)
		:stream(stream)
	{

	}

	void Read(byte* buffer, size_t length)
	{
		auto read = stream.Read(buffer, length);
		THROW_IF_NOT(read == length, "stream is insufficient.");
	}

	template<typename T, typename = std::enable_if_t<std::is_trivial<T>::value>>
	void Read(T* buffer)
	{
		Read((byte*)buffer, sizeof(T));
	}

	template<typename T, typename = std::enable_if_t<std::is_trivial<T>::value>>
	T Read()
	{
		T value;
		Read(&value);
		return std::move(value);
	}

	void Seek(int64_t offset, SeekOrigin origin)
	{
		stream.Seek(offset, origin);
	}
private:
	std::shared_ptr<Stream> stream_holder;
	Stream& stream;
};

NS_ED
NS_ED