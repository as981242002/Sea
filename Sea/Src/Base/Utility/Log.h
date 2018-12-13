#ifndef _UTILITY_LOG_H_
#define _UTILITY_LOG_H_

#include<fstream>
#include<iostream>
#include<time.h>
#include"LogStream.h"


namespace Sea
{

inline LogStream& operator<<(LogStream& s, const Fmt& fmt) noexcept
{
	s.append(fmt.data_(), fmt.length());
	return s;
}

LogStream& operator<<(LogStream& os, const tm& time) noexcept;

}

#endif // !_UTILITY_LOG_H_

