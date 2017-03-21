#include <stdio.h>
#include "event_manager.h"

/* void	event_manager_del(void *ptr) */
/* { */
/*   t_event_manager	*self; */

/*   self = ptr; */
/* } */

t_event_manager			*t_event_manager_new(t_event_manager_init var)
{
#ifdef	EVENT_SINGLETON
  static t_event_manager	*em = NULL;

  if (em != NULL)
    return (em);
#else
  t_event_manager		*em;
#endif
  if (var.size == 0)
    return (NULL);
  if ((em = newObject(t_event_manager)) == NULL)
    return (NULL);
  if ((em->events = new(t_circularBuff, var.size)) == NULL)
    return (NULL);
  em->max_events = var.size;
  return (em);
}

static t_event	*_get_event(t_event_manager *em)
{
  if (!em)
    return (NULL);
  return (CBGET(t_event *, em->events));
}

static int	_push_event(t_event_manager *em, t_event *ev)
{
  if (!em || !ev)
    return (EM_PARAM);
  return (CBPUT(em->events, ev));
}

static size_t		_event_count(t_event_manager *em)
{
  return (em->max_events - CBSIZE(em->events));
}

#ifdef EVENT_SINGLETON
t_event			*get_event()
{
  return (_get_event(new(t_event_manager)));
}

int		push_event(t_event *ev)
{
  return (_push_event(new(t_event_manager), ev));
}

size_t		event_count()
{
  return (_event_count(new(t_event_manager)));
}

#else
t_event *get_event(t_event_manager *em)
{
  return (_get_event(em));
}

int push_event(t_event_manager *em, t_event *ev)
{
  return (_push_event(em, ev));
}

size_t		event_count(t_event_manager *em)
{
  return (_event_count(em));
}

#endif
