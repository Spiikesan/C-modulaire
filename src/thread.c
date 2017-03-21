#include "thread.h"

void		thr_del(void *ptr)
{
  t_thread	*t;

  if (!ptr)
    return ;
  t = ptr;
#ifdef __linux__
  pthread_join(t->thread, t->ret);
#elif _WIN32
  WaitForSingleObject(t->thread.handle, INFINITE);
  GetExitCodeThread(t->thread.handle, t->ret);
  CloseHandle(t->thread.handle);
#endif
}

t_thread	*t_thread_new(t_thread_init var)
{
  t_thread	*t;

  if (!var.routine)
    return (NULL);
  if ((t = newObject(t_thread, &thr_del)) == NULL)
    return (NULL);
  t->ret = var.ret;
#ifdef __linux__
  if (pthread_create(&t->thread, NULL, var.routine, var.params) != 0)
    return (NULL);
#elif _WIN32
  t->thread.handle = CreateThread(NULL, 0,
				   (LPTHREAD_START_ROUTINE)var.routine,
				   var.params, 0, &(t->thread.thread_id));
  if (t->thread.handle == NULL)
    return (NULL);
#endif
  return (t);
}
