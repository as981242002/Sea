#ifndef BASE_BOUNDEDBLOCKINGQUEUE_H
#define BASE_BOUNDEDBLOCKINGQUEUE_H

#include "Condition.h"
#include "Mutex.h"

#include<boost/circular_buffer.hpp>
#include<assert.h>

namespace Sea
{

template<typename T>
class BoundedBlockingQueue : NonCopyable
{
public:
    explicit BoundedBlockingQueue(int maxSize) : mutex_(),
        notEmpty_(mutex_),
        notFull_(mutex_),
        queue_(maxSize)
    {
    }

    void put(const T& x)
    {
        MutexLockGuard lock(mutex_);
        while(queue_.full())
        {
            notFull_.wait();
        }
        assert(!queue_.full());
        queue_.push_back(x);
        notEmpty_.notify();
    }

    T take()
    {
        MutexLockGuard lock(mutex_);
        while(queue_.empty())
        {
            notEmpty_.wait();
        }
        assert(!queue.empty());
        T front(queue_.front());
        queue_.pop_front();
        notFull_.notify();
        return front;
    }

    bool empty() const
    {
        MutexLockGuard lock(mutex_);
        return queue_.empty();
    }

    bool full() const
    {
        MutexLockGuard lock(mutex_);
        return queue_.full();
    }

    size_t size() const
    {
        MutexLockGuard lock(mutex_);
        return  queue_.size();
    }

    size_t capacity() const
    {
        MutexLockGuard lock(mutex_);
        return queue_.capacity();
    }

private:
    mutable MutexLock mutex_;
    Condition notEmpty_ GUARDED_BY(mutex_);
    Condition notFull_ GUARDED_BY(mutex_);
    boost::circular_buffer<T> queue_ GUARDED_BY(mutex_);
};

}


#endif // BOUNDEDBLOCKINGQUEUE_H
