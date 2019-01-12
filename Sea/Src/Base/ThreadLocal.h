#ifndef BASE_THREADLOCAL_H
#define BASE_THREADLOCAL_H

#include "Mutex.h"
#include "NonCopyable.h"

#include <pthread.h>

namespace Sea
{

template <typename T>
class ThreadLocal:NonCopyable
{
public:
    ThreadLocal()
    {
        MCHECK(pthread_key_create(pkey_));
    }

    ~ThreadLocal()
    {
        MCHECK(pthread_key_delete(pkey_));
    }

    T& value()
    {
        T* perThreadValue = static_cast<T*>(pthread_getspecific(pkey_));
        if(!perThreadValue)
        {
            T* newObj = new T ();
            MCHECK(pthread_setspecific(pkey_, newObj));
            perThreadValue = newObj;
        }
        return *perThreadValue;
    }
private:
    static void destructor(void* x)
    {
        T* obj = static_cast<T*>(x);
        using T_must_be_complete_type = char[sizeof (T) == 0 ? -1 : 1];
        T_must_be_complete_type dummy;
        (void) dummy;
        delete  obj;
    }
private:
    pthread_key_t pkey_;
};

}//namespace Sea


#endif // THREADLOCAL_H
