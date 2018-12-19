#ifndef BASE_LOGGING_H
#define BASE_LOGGING_H

#include "../Base/Utility/LogStream.h"
#include "TimeZone.h"

namespace Sea
{

class TimeZone;

class Logger
{
public:
    enum Enum_LogLevel
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
        NUM_LOG_LEVELS,
    };

    class SourceFile
    {
    public:
        template<int N>
        SourceFile(const char(&arr)[N]):data_(arr),size_(N-1)
        {
            const char* slash = strrchr(data_, '/');
            if(slash)
            {
                data_ = slash + 1;
                size_ -= static_cast<int>(data_ - arr);
            }
        }

        explicit SourceFile(const char* filename) :data_(filename)
        {
            const char* slash = strrchr(filename, '/');
            if(slash)
            {
                data_ = slash + 1;
            }
            size_ = static_cast<int>(strlen(data_));
        }
        const char* data_;
        int size_;
    };

    Logger(SourceFile file, int line);
    Logger(SourceFile file, int line, Enum_LogLevel level);
    Logger(SourceFile file, int line, Enum_LogLevel level, const char* func);
    Logger(SourceFile file, int line, bool toAbort);
    ~Logger();

    LogStream& stream()
    {
        return impl_.stream_;
    }

    static Enum_LogLevel logLevel();
    static void setLogLevel(Enum_LogLevel level);

    typedef  void (*OutputFunc)(const char* msg, int len);
    typedef  void (*FlushFunc)();
    static void setOutput(OutputFunc);
    static void setFlush(FlushFunc);
    static void setTimeZone(const TimeZone& tz);
private:
    class Impl
    {
    public:
        using LogLevel = Logger::Enum_LogLevel ;
        Impl(LogLevel level, int old_errno, const SourceFile& file, int line);

        void formatTime();

        void finsh();

        Timestamap time_;
        LogStream stream_;
        LogLevel level_;
        int line_;
        SourceFile basename_;
    };

    Impl impl_;
};

extern Logger::Enum_LogLevel g_logLevel;

inline Logger::Enum_LogLevel Logger::logLevel()
{
    return g_logLevel;
}

#define LOG_TRACE if (Sea::Logger::logLevel() <= Sea::Logger::TRACE) \
    Sea::Logger(_FILE_, _LINE_, Sea::Logger::TRACE, _func_).stream()

#define LOG_DEBUG if (Sea::Logger::logLevel() <= Sea::Logger::DEBUG) \
    Sea::Logger(_FILE_, _LINE_, Sea::Logger::DEBUG, _func_).stream()

#define LOG_INFO if (Sea::Logger::logLevel() <= Sea::Logger::INFO) \
    Sea::Logger(_FILE_, _LINE_).stream()

#define LOG_WARN Sea::Logger(_FILE_,_LINE_, Sea::Logger::WARN).stream()
#define LOG_ERROR Sea::Logger(_FILE_,_LINE_, Sea::Logger::ERROR).stream()
#define LOG_FATAL Sea::Logger(_FILE_,_LINE_, Sea::Logger::FATAL).stream()
#define LOG_SYSERR Sea::Logger(_FILE_,_LINE_, false).stream()
#define LOG_SYSFATAL Sea::Logger(_FILE_,_LINE_, true).stream()

const char* strerror_tl(int savedErrno);

#define CHECK_NOTNULL(val) \
    ::Sea::CheckNotNull(_FILE_, _LINE_, "'"  #val "'  Must be non NULL", (val))

template<typename T>
T* CheckNotNull(Logger::SourceFile file, int line, const char* names, T* ptr)
{
    if(ptr == nullptr)
    {
        Logger(file, line, Logger::FATAL).stream() << names;
    }

    return ptr;
}

}//namespace Sea

#endif // LOGGING_H
