#ifndef BASE_BLOCKINGQUEUE_H
#define BASE_BLOCKINGQUEUE_H

#include<deque>
#include<assert.h>

#include"Condition.h"
#include"Mutex.h"

namespace Sea
{

template<typename T>
class BlockingQueue
{
public:
    BlockingQueue():mutex_(), queue_(), notEmpty_(mutex_) {}

    void put(const T& x)
    {
        MutexLockGuard  lock(mutex_);
        queue_.push_back(x);
        notEmpty_.notify();
    }

    void put(T&& x)
    {
        MutexLockGuard lock(mutex_);
        queue_.push_back(std::move(x));
        notEmpty_.notify();
    }

    T take()
    {
        MutexLockGuard lock(mutex_);
        while(queue_.empty())
        {
            notEmpty_.wait();
        }
        assert(!queue_.empty());
        T front(std::move(queue_.front()));
        queue_.pop_front();
        return  std::move(front);
    }

    size_t size() const
    {
        MutexLockGuard lock(mutex_);
        return queue_.size();
    }
private:
    mutable MutexLock mutex_;
    Condition notEmpty_ GUARDED_BY(mutex_);
    std::deque<T> queue_ GUARDED_BY(mutex_);
};

}

#endif // BLOCKINGQUEUE_H
