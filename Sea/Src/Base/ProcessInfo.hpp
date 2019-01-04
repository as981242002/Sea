#ifndef BASE_PROCESSINFO_HPP
#define BASE_PROCESSINFO_HPP

#include<vector>
#include<sys/types.h>

#include"Stringpiece.h"
#include"Timestamp.h"
#include"Types.h"

namespace Sea
{

namespace ProcessInfo
{

pid_t fid();

string pidString();

uid_t uid();

string username();
uid_t euid();
Timestamp startTime();
int clockTickPerSecond();
int pageSize();
bool isDebugBuild();

string hostname();
string procname();
StringPiece procname(const string& stat);

string procStatus();

string threadStat();

string procStat();

string exePath();

int openedFiles();
int maxOpenFiles();

struct CpuTime
{
    double userSeconds;
    double systemSeconds;

    CpuTime():userSeconds(0.0), systemSeconds(0.0)
    {}
};

int numThreads();
std::vector<pid_t> threads();
}//namespace processinfo


}//namespace Sea
#endif // PROCESSINFO_HPP
