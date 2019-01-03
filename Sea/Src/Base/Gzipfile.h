#ifndef BASE_GZIPFILE_H
#define BASE_GZIPFILE_H

#include<zlib.h>

#include"Stringpiece.h"
#include"NonCopyable.h"

namespace Sea
{

class GzipFile:NonCopyable
{
public:
GzipFile(GzipFile&& rhs) noexcept: file_(rhs.file_)
{
    rhs.file_ = nullptr;
}

~GzipFile()
{
    if(file_)
    {
        ::gzclose(file_);
    }
}

GzipFile& operator=(GzipFile&& rhs) noexcept
{
    swap(rhs);
    return *this;
}

bool valid() const
{
    return file_ != nullptr;
}

void swap(GzipFile& rhs)
{
    std::swap(file_, rhs.file_);
}

#if ZLIB_VERNUM >= 0x1240
bool setBuffer(int size)
{
    return ::gzbuffer(file_, size) == 0;
}

off_t offset() const
{
    return ::gzoffset(file_);
}
#endif

int read(void* buf, int len)
{
    return ::gzread(file_, buf, len);
}

int write(StringPiece buf)
{
     return ::gzwrite(file_, buf.data(), buf.size());
}

off_t tell() const
{
    return ::gztell(file_);
}


static GzipFile openForRead(StringArg fileName)
{
    return GzipFile(::gzopen(fileName.c_str(), "rbe"));
}

static GzipFile openForAppend(StringArg fileName)
{
    return GzipFile(::gzopen(fileName.c_str(), "abe"));
}

static GzipFile openForWriteExclusive(StringArg fileName)
{
    return GzipFile(::gzopen(fileName.c_str(), "wbxe"));
}

static GzipFile openForWriteTruncate(StringArg fileName)
{
    return GzipFile(::gzopen(fileName.c_str(), "wbe"));
}
private:
explicit GzipFile(gzFile file):file_(file)
{
}

gzFile file_;
};

}

#endif // GZIPFILE_H
