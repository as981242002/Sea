#include<algorithm>
#include<stdexcept>
#include<string>
#include<vector>
#include<cassert>
#include<cstdint>
#include<cstdio>

#include"../Base/Date.h"
#include"../Base/NonCopyable.h"
#include"../Base/TimeZone.h"

namespace Sea
{

namespace detail
{

struct Transition
{
	time_t gmttime;
	time_t localtime;
	int localtimeIdx;

	Transition(time_t t, time_t l, int localtIdx) :gmttime(t), localtime(l), localtimeIdx(localtIdx)
	{

	}
};

struct Comp
{
	bool compareGmt;

	Comp(bool gmt) :compareGmt(gmt)
	{

	}

	bool operator()(const Transition& lhs, const Transition& rhs) const
	{
		if (compareGmt)
		{
			return lhs.gmttime < rhs.gmttime;
		}
		else
		{
			return lhs.localtime < rhs.localtime;
		}
	}

	bool equal(const Transition& lhs, const Transition& rhs) const
	{
		if (compareGmt)
		{
			return lhs.gmttime == rhs.gmttime;
		}
		else
		{
			return lhs.localtime == rhs.localtime;
		}
	}
};

struct Localtime
{
	time_t gmtOffset;
	bool isDst;
	int arrbIdx;

	Localtime(time_t offset, bool dst, int arrb) :gmtOffset(offset), isDst(dst), arrbIdx(arrb)
	{

	}
};

inline void fillHMS(unsigned seconds, struct tm* utc)
{
	utc->tm_sec = seconds % 60;
	unsigned minutes = seconds / 60;
	utc->tm_min = minutes % 60;
	utc->tm_hour = minutes / 60;
}

const int kSecondsPerDay = 24 * 60 * 60;

}//naemspace detail
}

using namespace Sea;
using namespace std;

struct TimeZone::Data
{
	vector<detail::Transition> transitions;
	vector<detail::Localtime> localtimes;
	vector<string> names;
	string abbrviation;
};

namespace Sea
{

namespace detail
{
class File
{
public:
	File(const char* file):fp_(::fopen(file, "rb"))
	{

	}

	~File()
	{
		if (fp_)
		{
			::fclose(fp_);
		}
	}

	bool valid() const
	{
		return fp_;
	}

	string readBytes(int n)
	{
		auto buf = make_shared<char[]>(n);
		
	}
private:
	FILE* fp_;
};


}

}
