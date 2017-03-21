#ifndef CROSS_MUTEX_H_
#define CROSS_MUTEX_H_

#ifdef __linux__
#include <pthread.h>
#elif _WIN32
#include <windows.h>
#endif

#ifdef __linux__
typedef pthread_mutex_t t_cmutex;
#elif _WIN32
typedef HANDLE t_cmutex;
#endif

int	cmutex_init(t_cmutex *ptr_mutex);
int	cmutex_lock(t_cmutex *ptr_mutex);
int	cmutex_unlock(t_cmutex *ptr_mutex);
int	cmutex_wait(t_cmutex *ptr_mutex);

#endif
