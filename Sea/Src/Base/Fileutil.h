#ifndef BASE_FILEUTIL_H
#define BASE_FILEUTIL_H

#include "NonCopyable.h"
#include "Stringpiece.h"
#include <sys/types.h>

namespace Sea
{

namespace  FileUtil
{

class ReadSmallFile:private NonCopyable
{
public:
    ReadSmallFile(StringArg filename);
    ~ReadSmallFile();

    template<typename String>
    int readToSting(int maxsize,
                    String* content,
                    int64_t* fileSize,
                    int64_t* modifyTime,
                    int64_t* createTime);

    int readToBuffer(int* size);

    const char* buffer() const { return buf_; }

    static const int kBUfferSize = 64 * 1024;
private:
    int fd_;
    int err_;
    char buf_[kBUfferSize];
};

template<typename String>
int readFile(StringArg filename,
             int maxSize,
             String* content,
             int64_t* fileSize = nullptr,
             int64_t* modifyTime = nullptr,
             int64_t* createTime = nullptr)
{
    ReadSmallFile file(filename);
    return file.readToSting(maxSize, content, fileSize, modifyTime, createTime);
}


class AppendFile: private NonCopyable
{
public:
    explicit AppendFile(StringArg filename);

    ~AppendFile();

    void append(const char* logline, size_t len);

    void flush();

    off_t writtenBytes() const
    {
        return writtenBytes_;
    }

    static const int kBufferSize = 64 * 1024;
private:
    size_t write(const char* logline, size_t len);

    FILE* fp_;
    off_t writtenBytes_;
    char buffer_[kBufferSize];
};

} //namespace FileUtil

} //namespace Sea

#endif // BASE_FILEUTIL_H
