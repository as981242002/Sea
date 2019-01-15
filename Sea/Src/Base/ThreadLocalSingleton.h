#ifndef BASE_THREADLOCALSINGLETON_H
#define BASE_THREADLOCALSINGLETON_H

#include "NonCopyable.h"

#include <assert.h>
#include <pthread.h>

namespace Sea
{

template <typename T>
class ThreadLocalSingleton:NonCopyable
{
public:
ThreadLocalSingleton() = delete ;
~ThreadLocalSingleton() = delete ;

static T& instance()
{

}

private:

static void destructor(void* obj)
{
    assert(obj == t_value_);
    using T_must_be_complete_type = char[sizeof (T) == 0 ? - 1 : 1];
    T_must_be_complete_type dummy;
    (void) dummy;
    delete  t_value_;
    t_value_ = 0;
}

class Deleter
{
public:
    Deleter()
    {
        pthread_key_create(&pkey_, &ThreadLocalSingleton::destructor);
    }

    ~Deleter()
    {
        pthread_key_delete(pkey_);
    }

    void set(T* newObj)
    {
        assert(pthread_getspecific(pkey_) == nullptr);
        pthread_setspecific(pkey_, newObj);
    }
    pthread_key_t pkey_;
};

static __thread T* t_value_;
static Deleter deleter_;
};

template <typename T>
__thread T* ThreadLocalSingleton<T>::t_value_ = 0;

template <typename T>
typename ThreadLocalSingleton<T>::Deleter ThreadLocalSingleton<T>::deleter_;

}//namespace Sea

#endif // THREADLOCALSINGLETON_H
