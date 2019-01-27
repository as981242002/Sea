#include "FileUtil.h"
#include "LogFile.h"
#include "ProcessInfo.h"

#include <assert.h>
#include <stdio.h>
#include <time.h>

using namespace Sea;


LogFile::LogFile(const string &basename, off_t rollsize, bool threadSafe, int flushInterval, int checkEveryN)
    :basename_(basename),
    rollsize_(rollsize),
    flushInterval_(flushInterval),
    checkEveryN_(checkEveryN),
    count_(0),
    mutex_(threadSafe ? new MutexLock() : nullptr),
    startOfPeriod_(0),
    lastRoll_(0),
    lastFlush_(0)
{
    assert(basename.find('/') == string:: npos);
    rollFile();
}

LogFile::~LogFile() = default;

void LogFile::append(const char *logfile, int len)
{
    if(mutex_)
    {
        MutexLockGuard lock(*mutex_);
        append_unlocked(logfile, len);
    }
    else
    {
        append_unlocked(logfile, len);
    }
}

void LogFile::flush()
{
    if(mutex_)
    {
        MutexLockGuard lock(*mutex_);
        file_->flush();
    }
    else
    {
        file_->flush();
    }
}


void LogFile::append_unlocked(const char *logline, int len)
{
    file_->append(logline, len);

    if(file_->writtenBytes() > rollsize_)
    {
        rollFile();
    }
    else
    {
        ++count_;
        if(count_ >= checkEveryN_)
        {
            count_ = 0;
            time_t now = ::time(nullptr);
            time_t thisPeriod_ =  now / kRollPerSeconds_ * kRollPerSeconds_;
            if(thisPeriod_ != startOfPeriod_)
            {
                rollFile();
            }
            else if(now - lastFlush_ > flushInterval_)
            {
                lastFlush_ = now;
                file_->flush();
            }

        }
    }
}

string LogFile::getLogFileName(const string &basename, time_t *now)
{
    string filename;
    filename.reserve(basename.size() + 64);
    filename = basename;

    char timebuf[32];
    struct tm tm;
    *now = time(nullptr);
    gmtime_r(now, &tm);
    strftime(timebuf, sizeof(timebuf), ".%Y%m%d-%H%M%S.", &tm);
    filename += timebuf;

    filename += ProcessInfo::hostname();

    char pidbuf[32];
    snprintf(pidbuf, sizeof (pidbuf), ".%d", ProcessInfo::pid());
    filename += pidbuf;

    filename += ".log";

    return filename;
}
