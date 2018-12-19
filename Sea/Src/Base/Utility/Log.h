#ifndef UTILITY_LOG_H
#define UTILITY_LOG_H

#include<fstream>
#include<iostream>
#include<time.h>
#include"LogStream.h"


namespace Sea
{

LogStream& operator<<(LogStream& os, const tm& time) noexcept;

}

#endif // !UTILITY_LOG_H

