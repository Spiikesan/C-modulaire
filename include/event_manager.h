#ifndef EVENT_MANAGER_H_
# define EVENT_MANAGER_H_

# include "new.h"
# include "circularBuff.h"
# include "event.h"

/*
** You have to compile with -DEVENT_SINGLETON to use the singleton feature
*/

# define EM_NOMORE	CBF_NOMORE
# define EM_NOERR	CBF_NOERR
# define EM_NOPLACE	CBF_NOPLACE
# define EM_PARAM	(-1)

/* size is the max number of events that can be stocked */
typedef struct	s_event_manager_init
{
  size_t	size;
}		t_event_manager_init;

typedef struct		s_event_manager
{
  t_object		__obj__;
  size_t		max_events;
  t_circularBuff	*events;
}			t_event_manager;

t_event_manager	*t_event_manager_new(t_event_manager_init var);

# ifdef EVENT_SINGLETON

t_event		*get_event();
int		push_event(t_event *ev);
size_t		event_count();

# else

t_event		*get_event(t_event_manager *em);
int		push_event(t_event_manager *em, t_event *ev);
size_t		event_count(t_event_manager *em);

# endif

#endif /* !EVENT_MANAGER_H_ */
