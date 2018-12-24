#ifndef BASE_TIMESTAMP_H
#define BASE_TIMESTAMP_H


#include "Copyable.h"
#include "Types.h"

#include<boost/operators.hpp>

namespace Sea
{
class Timestamp:public Copyable,
        public boost::equality_comparable<Timestamp>,
        public boost::less_than_comparable<Timestamp>
{
public:
    Timestamp():microSecondsSinceEpoch_(0){}

    explicit Timestamp(int64_t t):microSecondsSinceEpoch_(t){}

    void swap(Timestamp& that)
    {
        std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
    }

    string toString() const;
    string toFormatString(bool showMicroseconds = true) const;

    bool valid()const
    {
        return microSecondsSinceEpoch_ > 0;
    }

    int64_t microSecondsSinceEpoch() const
    {
        return microSecondsSinceEpoch_ ;
    }

    time_t secondsSinceEpoch() const
    {
        return static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
    }

    static Timestamp now();
    static Timestamp invalid()
    {
        return Timestamp();
    }

    static Timestamp fromUnixTime(time_t t, int microSeconds = 0)
    {
        return Timestamp(static_cast<int64_t>(t) * kMicroSecondsPerSecond + microSeconds);
    }

    static const int kMicroSecondsPerSecond = 1000 * 1000;
private:
    int64_t microSecondsSinceEpoch_;
};

inline bool operator<(Timestamp lhs, Timestamp rhs)
{
    return lhs.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
}

inline bool operator==(Timestamp lhs, Timestamp rhs)
{
    return lhs.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch();
}

inline double timeDifference(Timestamp high, Timestamp low)
{
    int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
    return  static_cast<double>(diff/Timestamp::kMicroSecondsPerSecond);
}

inline Timestamp addTime(Timestamp timestamp, double seconds)
{
    int64_t delta = static_cast<int64_t>(seconds * Timestamp::kMicroSecondsPerSecond);
    return Timestamp(timestamp.microSecondsSinceEpoch() + delta);
}

}//namespace Sea

#endif // TIMESTAMP_H
