#ifndef SEA_BASE_TIMEZONE_H_
#define SEA_BASE_TIMEZONE_H_

#include<memory>
#include<time.h>
#include"Copyable.h"

namespace Sea
{

class TimeZone : public Copyable
{
public:
	explicit TimeZone(const char* zonefile);
	TimeZone(int eastOfUTC, const char* tzname);
	TimeZone() = default;
	
	//default ator
	bool valid() const
	{
		return static_cast<bool> (data_);
	}
	
    struct tm toLocalTime(time_t seconds) const;
	time_t fromLocalTime(const struct tm&) const;

	
	static struct tm toUTCTime(time_t secondsSinceEpoch, bool yday = false);
	static time_t fromUTCTime(const struct tm&);
	
	static time_t fromUTCTime(int year, int month, int day, int hour, int minute, int seconds);

	struct Data;

private:
	std::shared_ptr<Data> data_;
};

}//namespace Sea

#endif // !SEA_BASE_TIMEZONE_H_
