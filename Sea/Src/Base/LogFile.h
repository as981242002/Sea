#ifndef BASE_LOGFILE_HPP
#define BASE_LOGFILE_HPP

#include "Mutex.h"
#include "Types.h"

#include <memory>

namespace Sea
{

namespace FileUtil
{
class AppendFile;

} // namespace FileUtil

class LogFile: NonCopyable
{
public:
    LogFile(const string& basename,
            off_t rollsize,
            bool threadSafe = true,
            int flushInterval = 1,
            int checkEveryN = 1024);
    ~LogFile();
    void append(const char* logfile, int len);
    void flush();
    bool rollFile();

private:
    void append_unlocked(const char* logline, int len);

    static string getLogFileName(const string& basename, time_t* now);

    const string basename_;
    const off_t rollsize_;
    const int flushInterval_;
    const int checkEveryN_;

    int count_;
    std::unique_ptr<MutexLock> mutex_;
    time_t startOfPeriod_;
    time_t lastRoll_;
    time_t lastFlush_;
    std::unique_ptr<FileUtil::AppendFile> file_;
    const static int kRollPerSeconds_ = 60 * 60 * 24;
};

}

#endif // LOGFILE_HPP
