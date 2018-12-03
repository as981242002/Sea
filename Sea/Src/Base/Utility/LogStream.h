#ifndef _UTILITY_LOGSTREAM_H_
#define _UTILITY_LOGSTREAM_H_

#include<string>
#include<cassert>
#include<cstring>
#include "../NonCopyable.h"
#include "../Utility/Utility.h"

namespace Sea
{
namespace Detail
{
const int iSmallBufferSize = 2000;
const int iMaxBufferSize = 2000 * 1000;

template<size_t SIZE>
class FixedBuffer : private NonCopyable
{
public:
	FixedBuffer() :cur_(data_) {}
	~FixedBuffer() = default;

	const char* data() const noexcept { return data_; }
	int length()const noexcept { return static_cast<int>(cur_ - data_); }
	char* current() noexcept { return cur_; }
	int avail() const noexcept { return static_cast<int> (end() - cur_); }
	void add(size_t len) noexcept { cur_ += len; }
	void append(const char* ptr, size_t len) noexcept
	{
		if (static_cast<size_t> (avail()) > len)
		{
			memcpy(cur_, ptr, len);
			cur_ += len;
		}
	}

	void reset() noexcept { cur_ = data_; }
	void bzero() noexcept { Sea::bzero(data_, sizeof(data_)); reset(); }

	std::string tostring() const { return std::string(data_, length()); }
private:
	char* cur_;
	char data_[SIZE] = { 0 };

	const char* end() const noexcept { return (data_ + sizeof(data_)); }
};
}

class LogStream : private NonCopyable
{
	using self = LogStream;
public:
	LogStream() {}
	~LogStream() {}

	using Buffer = Detail::FixedBuffer<Detail::iSmallBufferSize>;

	self& operator<< (bool v) noexcept
	{
		buffer_.append(v ? "1" : "0", 1);
		return *this;
	}

	self& operator<<(short) noexcept;
	self& operator<<(unsigned short) noexcept;
	self& operator<<(int) noexcept;
	self& operator<<(unsigned int) noexcept;
	self& operator<<(long) noexcept;
	self& operator<<(unsigned long) noexcept;
	self& operator<<(long long) noexcept;
	self& operator<<(unsigned long long) noexcept;

	self& operator<<(const void*) noexcept;
	self& operator<<(double v) noexcept;
	self& operator<<(float v) noexcept
	{
		*this << static_cast<double>(v);
	}

	self& operator<<(char v) noexcept
	{
		buffer_.append(&v, 1);
	}

	self& operator<<(const char* pstr) noexcept
	{
		pstr ? buffer_.append(pstr, strlen(pstr)) : buffer_.append("(null)", 6);
		return *this;
	}

	self& operator<<(const unsigned char* pstr) noexcept
	{
		return operator<<(reinterpret_cast<const char*>(pstr));
	}

	self& operator<<(const std::string& str) noexcept
	{
		buffer_.append(str.c_str(), str.size());
		return *this;
	}

	self& operator<<(Buffer& buff) noexcept
	{
		*this << buff.tostring();
		return *this;
	}

	void append(const char* pstr, const int len) noexcept { buffer_.append(pstr, len); }
	const Buffer& buffer() noexcept { return buffer_; }
	void reset() noexcept { buffer_.reset(); }
	void clear() noexcept { buffer_.bzero(); };
	int length() noexcept { return buffer_.length(); };
	//DeBugº¯Êý
	const char* print() const { return buffer_.data(); }
private:
	Buffer buffer_;

	template<typename T>
	void formatInteger(T v);

	static const int iMaxNumbericSize = 32;
};

class Fmt
{
public:
	template<typename T>
	Fmt(const char* fmt, T val);
	~Fmt() = default;

	const char* data_() const { return buf_; }
	int length() const { return length_; }
private:
	char buf_[32] = { 0 };
	int length_;
};

} //namespace Sea

#endif // !_UTILITY_LOGSTREAM_H_
