#ifndef BASE_SINGLETON_H
#define BASE_SINGLETON_H

#include "NonCopyable.h"

#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

namespace Sea
{

namespace detail
{

template <typename T>
struct has_no_destory
{
    template<typename C> static char test(decltype (&C::no_destory));
    template<typename C> static int32_t test(...);
    const static bool value = sizeof (test<T>(0)) == 1;
};

}//namespace detail

template <typename T>
class Singleton: NonCopyable
{
public:
    Singleton() = delete ;
    ~Singleton() = delete ;

    static T& instance()
    {
        pthread_once(&ponce_, &Singleton::init);
        assert(value_!=nullptr);
        return *value_;
    }
private:
    static void destory()
    {
        using T_must_be_complete_type = char[sizeof (T) == 0 ? -1 : 1];
        T_must_be_complete_type dummy;
        (void) dummy;

        delete value_;
        value_ = nullptr;
    }

    static void init()
    {
        value_ = new T();
        if(!detail::has_no_destory<T>::value)
        {
            ::atexit(destory);
        }
    }

private:
    static pthread_once_t ponce_;
    static T* value_;
};


template <typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template <typename T>
T* Singleton<T>::value_ = nullptr;

}//namespace  Sea


#endif // SINGLETON_H
