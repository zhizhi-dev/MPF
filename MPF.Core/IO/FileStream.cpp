//
// MPF
// 文件流
//
// (c) SunnyCase 
// 创建日期 2015-03-09
#include "stdafx.h"
#include "../stdafx.h"
#include "../../include/io/FileStream.h"
#include <cpprest/filestream.h>

using namespace MPF;
using namespace MPF::IO;

inline DWORD ToDWORD(AccessMode mode)
{
	if (mode == AccessMode::Read)
		return GENERIC_READ;
	else if (mode == AccessMode::Write)
		return GENERIC_WRITE;
	else if (mode == AccessMode::ReadWrite)
		return GENERIC_READ | GENERIC_WRITE;

	throw std::exception("unexpected access mode.");
}

inline DWORD ToDWORD(CreationDeposition creation)
{
	switch (creation)
	{
	case CreationDeposition::Create:
		return CREATE_ALWAYS;
	case CreationDeposition::CreateNew:
		return CREATE_NEW;
	case CreationDeposition::Open:
		return OPEN_ALWAYS;
	case CreationDeposition::OpenExisting:
		return OPEN_EXISTING;
	default:
		throw std::exception("unexpected access mode.");
	}
}

FileStream::FileStream(const String& fileName, AccessMode accessMode, CreationDeposition creation)
	:offset(0)
{
	auto file = CreateFile(fileName.GetDataPointer(), ToDWORD(accessMode), 0, NULL,
		ToDWORD(creation), FILE_ATTRIBUTE_NORMAL, NULL);
	handle.reset(file);
	THROW_WIN_IFNOT(file != INVALID_HANDLE_VALUE);
}

FileStream::~FileStream()
{

}

bool FileStream::GetCanSeek() const noexcept
{
	return true;
}

uint64_t FileStream::GetSize() const
{
	LARGE_INTEGER size;
	THROW_WIN_IFNOT(GetFileSizeEx(handle.get(), &size));
	return size.QuadPart;
}

size_t FileStream::Read(byte* buffer, size_t length)
{
	OVERLAPPED overlapped{ 0 };
	overlapped.Offset = (DWORD)offset;
	overlapped.OffsetHigh = (DWORD)(offset >> 32);

	DWORD read = 0;
	THROW_WIN_IFNOT(ReadFile(handle.get(), buffer, length, &read, &overlapped));
	offset += read;
	return read;
}

size_t FileStream::Write(const byte* buffer, size_t length)
{
	OVERLAPPED overlapped{ 0 };
	overlapped.Offset = (DWORD)offset;
	overlapped.OffsetHigh = (DWORD)(offset >> 32);

	DWORD written = 0;
	THROW_WIN_IFNOT(WriteFile(handle.get(), buffer, length, &written, &overlapped));
	offset += written;
	return written;
}

void FileStream::Seek(int64_t offset, SeekOrigin origin)
{
	if (offset < 0)
	{
		uint64_t noffset = -offset;
		switch (origin)
		{
		case SeekOrigin::Current:
			Seek(this->offset - noffset, SeekOrigin::Begin);
			break;
		case SeekOrigin::End:
			Seek(GetSize() - noffset, SeekOrigin::Begin);
			break;
		default:
			throw std::out_of_range("file offset out of range.");
		}
	}
	else if (offset > 0)
	{
		switch (origin)
		{
		case SeekOrigin::Begin:
			if (offset > GetSize())
				throw std::out_of_range("file offset out of range.");
			this->offset = offset;
			break;
		case SeekOrigin::Current:
			Seek(this->offset + offset, SeekOrigin::Begin);
			break;
		default:
			throw std::out_of_range("file offset out of range.");
		}
	}
	else
	{
		switch (origin)
		{
		case SeekOrigin::Begin:
			this->offset = 0;
			break;
		case SeekOrigin::End:
			this->offset = GetSize();
			break;
		}
	}
}