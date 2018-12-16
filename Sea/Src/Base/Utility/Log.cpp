#include"Log.h"

namespace Sea
{

LogStream& operator<<(LogStream& os, const tm& time) noexcept
{
	char str[128] = { 0 };
	strftime(str, sizeof(str), "%Y-%m-%d %H-%M-%S", &time);
	os << str;

	return os;
}

}
