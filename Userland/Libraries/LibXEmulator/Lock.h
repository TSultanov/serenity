#include <pthread.h>

#ifdef __cplusplus
namespace XLib {
extern "C" {
#endif

#define register
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#undef register
#ifdef __cplusplus
}
}
#endif

#ifdef __cplusplus
struct XLib::_XLockInfo {
#else
struct _XLockInfo {
#endif
    pthread_mutex_t mutex;
};

#ifdef __cplusplus
typedef struct XLib::_XLockInfo LockInfoRec;
#else
typedef struct _XLockInfo LockInfoRec;
#endif

#undef _XLockMutex
#undef _XUnlockMutex
#undef _XCreateMutex
#undef _XFreeMutex

static inline void
#ifdef __cplusplus
_XCreateMutex(struct XLib::_XLockInfo* info)
#else
_XCreateMutex(struct _XLockInfo* info)
#endif
{
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(&info->mutex, &attr);
}

#define _XLockMutex(LOCK)	pthread_mutex_lock(&(LOCK)->mutex)
#define _XUnlockMutex(LOCK)	pthread_mutex_unlock(&(LOCK)->mutex)
#define _XFreeMutex(LOCK)	pthread_mutex_destroy(&(LOCK)->mutex);
