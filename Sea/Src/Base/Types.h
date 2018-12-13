#ifndef SEA_BASE_TYPES_H_
#define SEA_BASE_TYPES_H_

#include<cstdint>
#include<cstring>
#include<string>

#ifndef NDEBUG
#include<assert.h>
#endif // NDEBUG


namespace Sea
{
using std::string;

inline void memZero(void* p, size_t n)
{
	memset(p, 0, n);
}

// Taken from google-protobuf stubs/common.h
//
// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
// http://code.google.com/p/protobuf/
// Author: kenton@google.com (Kenton Varda) and others

template<typename To, typename From>
inline To implicit_cast(const From& f)
{
	return f;
}

template<typename To, typename From>
inline  To down_cast(From* f)
{
	if (false)
	{
		implicit_cast<From*, To>(0);
	}
#if !defined(NDEBUG) && !defined(GOOGLE_PROTOBUF_NO_RTTI)
	assert(f == nullptr || dynamic_cast<To>(f) != nullptr);  //debug模式才有用
#endif
	return static_cast<To>(f);
}

} //namespace Sea


#endif // !SEA_BASE_TYPES_H_
