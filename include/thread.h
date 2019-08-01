#ifndef THREAD_H_
# define THREAD_H_

# ifdef __linux__
#  include <pthread.h>

typedef pthread_t	t_cthread;
typedef void		*t_cth_ret;
typedef void		*t_cth_params;

# elif _WIN32
#  include <windows.h>

typedef struct	s_cthread
{
  DWORD		thread_id;
  HANDLE	handle;
}		t_cthread;

typedef DWORD t_cth_ret;
typedef LPVOID t_cth_params;

# endif

typedef t_cth_ret	(*t_thread_routine)(t_cth_params);

# include "object.h"

# define t_thread_DEFINITION	\
	t_thread,					\
	(t_thread_routine, routine),\
	(t_cth_params, params),		\
	(t_cth_ret,	ret),			\
	(t_cthread,	thread)			\

CMETA_STRUCT_DEF(t_thread_DEFINITION);

#endif /* !THREAD_H_ */
