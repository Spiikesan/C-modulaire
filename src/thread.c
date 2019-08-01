#include "thread.h"

void		thr_del(t_object *ptr)
{
  t_thread	*t;

  if (!ptr)
    return ;
  t = (t_thread *)ptr;
#ifdef __linux__
  if (t->thread)
	  pthread_join(t->thread, t->ret);
#elif _WIN32
  if (t->thread.handle) {
	  WaitForSingleObject(t->thread.handle, INFINITE);
	  GetExitCodeThread(t->thread.handle, &t->ret);
	  CloseHandle(t->thread.handle);
  }
#endif
}

CMETA_STRUCT_BUILD(t_thread_DEFINITION)
{
  t_thread	*t = newObject(t_thread, &thr_del);

  if (t) {
	  if (args.routine)
	  {
		  t->ret = args.ret;
#ifdef __linux__
		  if (pthread_create(&t->thread, NULL, args.routine, args.params) != 0)
			  delete(t);
#elif _WIN32
		  t->thread.handle = CreateThread(NULL, 0,
				   (LPTHREAD_START_ROUTINE)args.routine,
				   args.params, 0, &(t->thread.thread_id));
		  if (t->thread.handle == NULL)
			  delete(t);
#endif
	  } else
		  delete(t);
  }
  return (t);
}
