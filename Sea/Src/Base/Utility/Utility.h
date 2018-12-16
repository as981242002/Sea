#ifndef SEA_BASE_BASE_H_
#define SEA_BASE_BASE_H_

#include<memory.h>
#include<time.h>

namespace Sea
{

static const tm GetNowTime()noexcept
{
	time_t nowtime;
	time(&nowtime);

    tm now = {0};
    localtime_r(&nowtime, &now);

	return now;
}

static void bzero(char* ptr, int n) noexcept
{
	memset(ptr, 0, n);
}

}

#endif // !SEA_BASE_BASE_H_
