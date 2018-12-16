#ifndef SEA_BASE_DATE_H_
#define	SEA_BASE_DATE_H_

#include"../Base/Copyable.h"
#include"../Base/Types.h"

struct tm;

namespace Sea
{

class Date: public Sea::Copyable
{
public:
    Date() :julianDayNumber_(0) {}
	
	Date(int year, int month, int day);
	
	explicit Date(int julianDayNumber) : julianDayNumber_(julianDayNumber) {}
	
	explicit Date(const struct tm&);

	void swap(Date& lhs)
	{
		std::swap(julianDayNumber_, lhs.julianDayNumber_);
	}

	bool valid() const
	{
		return julianDayNumber_ > 0;
	}

	struct YearMonthDay
	{
		int year;//1900-2500
		int month; //1-12
		int day;//1-31
	};
	using YearMonthDay = struct YearMonthDay;
	
	string toIsoString() const;
	
	YearMonthDay yearMonthDay() const;

	int year() const
	{
		return yearMonthDay().year;
	}

	int month() const
	{
		return yearMonthDay().month;
	}

	int day() const
	{
		return yearMonthDay().day;
	}
	
	int weekDay() const
	{
		return (julianDayNumber_ + 1) % kDayPerWeek;
	}

	int julianDayNumber() const
	{
		return julianDayNumber_;
	}

	static const int kDayPerWeek = 7;
	static const int kJulianDayOf1970_01_01;
private:
	int julianDayNumber_;
};

inline bool operator<(const Date& lhs, const Date& rhs)
{
	return lhs.julianDayNumber() < rhs.julianDayNumber();
}

inline bool operator ==(const Date& lhs, const Date& rhs)
{
	return lhs.julianDayNumber() == rhs.julianDayNumber();
}

}//namespace Sea

#endif // !SEA_BASE_DATE_H_
