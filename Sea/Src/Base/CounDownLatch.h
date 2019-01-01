#ifndef BASE_COUNDOWNLATCH_H
#define BASE_COUNDOWNLATCH_H

#include "Condition.h"
#include "Mutex.h"

namespace Sea
{

class CountDownLatch : NonCopyable
{
public:
    explicit CountDownLatch(int count);

    void wait();

    void countDown();

    int getCount() const;

private:
    mutable MutexLock mutex_;
    Condition condition_ GUARDED_BY(mutex_);
    int count_ GUARDED_BY(mutex_);
};

}
#endif // COUNDOWNLATCH_H
