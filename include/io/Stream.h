//
// MPF
// 流
//
// (c) SunnyCase 
// 创建日期 2015-03-09
#pragma once
#include "../Type.h"

NS_MPF
NS_IO

enum class SeekOrigin
{
	Begin,
	Current,
	End
};

// 流
class Stream
{
public:
	Stream(){}
	virtual ~Stream(){}

	virtual bool GetCanSeek() const noexcept = 0;
	virtual uint64_t GetSize() const = 0;

	virtual size_t Read(byte* buffer, size_t length) = 0;
	virtual size_t Write(const byte* buffer, size_t length) = 0;
	virtual void Seek(int64_t offset, SeekOrigin origin) = 0;
};

NS_ED
NS_ED