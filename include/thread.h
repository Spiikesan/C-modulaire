#ifndef THREAD_H_
# define THREAD_H_

# ifdef __linux__
#  include <pthread.h>
# elif _WIN32
#  include <windows.h>
# endif

# include "new.h"

# ifdef __linux__

typedef pthread_t	t_cthread;
typedef void		*t_cth_ret;
typedef void		*t_cth_params;

# elif _WIN32

typedef struct	s_cthread
{
  DWORD		thread_id;
  HANDLE	handle;
}		t_cthread;

typedef DWORD t_cth_ret;
typedef LPVOID t_cth_params;

# endif

typedef struct	s_thread_init
{
  t_cth_ret	(*routine)(t_cth_params);
  t_cth_params	params;
  t_cth_ret	ret;
}		t_thread_init;

typedef struct	s_thread
{
  t_object	__obj__;
  t_cth_ret	ret;
  t_cthread	thread;
}		t_thread;

t_thread	*t_thread_new(t_thread_init var);

#endif /* !THREAD_H_ */
