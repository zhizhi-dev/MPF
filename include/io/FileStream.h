//
// MPF
// 文件流
//
// (c) SunnyCase 
// 创建日期 2015-03-09
#pragma once
#include "Stream.h"
#include "../platform.h"
#include "../String.h"

NS_MPF
NS_IO

// 访问模式
enum class AccessMode
{
	// 可读
	Read,
	// 可写
	Write,
	// 可读写
	ReadWrite
};

// 创建选项
enum class CreationDeposition
{
	// 如果不存在则创建新的
	Create,
	// 创建新的，如果存在则产生异常
	CreateNew,
	// 如果存在则打开，否则创建新的
	Open,
	// 打开，如果不存在则产生异常
	OpenExisting,
	// 打开并清除，如果不存在则产生异常
	Truncate
};

// 文件流
class FileStream : public Stream
{
public:
	MPF_API FileStream(const String& fileName, AccessMode accessMode = AccessMode::ReadWrite,
		CreationDeposition creation = CreationDeposition::Create);
	MPF_API virtual ~FileStream();

	MPF_API virtual bool GetCanSeek() const noexcept;
	MPF_API virtual uint64_t GetSize() const;

	MPF_API virtual size_t Read(byte* buffer, size_t length);
	using Stream::Write;
	MPF_API virtual size_t Write(const byte* buffer, size_t length);
	MPF_API virtual void Seek(int64_t offset, SeekOrigin origin);
private:
	FileStream(const FileStream&) = delete;
	FileStream& operator=(const FileStream&) = delete;
private:
	unique_handle handle;
	uint64_t offset;
};

NS_ED
NS_ED