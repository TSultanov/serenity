#include <pthread.h>

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
}
}

struct XLib::_XLockInfo {
    pthread_mutex_t mutex;
};

typedef struct XLib::_XLockInfo LockInfoRec;

#undef _XLockMutex
#undef _XUnlockMutex
#undef _XCreateMutex
#undef _XFreeMutex

static inline void
_XCreateMutex(struct XLib::_XLockInfo* info)
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&info->mutex, &attr);
}

#define _XLockMutex(LOCK)	pthread_mutex_lock(&(LOCK)->mutex)
#define _XUnlockMutex(LOCK)	pthread_mutex_unlock(&(LOCK)->mutex)
#define _XFreeMutex(LOCK)	pthread_mutex_destroy(&(LOCK)->mutex);
