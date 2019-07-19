#include <string.h>
#include <stdio.h>
#include "event_manager.h"
#include "foreach.h"

void t_event_delete(void *ptr)
{
	t_event_manager	*man;

	if (ptr)
	{
		man = (t_event_manager *)ptr;
		/*FOREACH(t_pair *, p, man->events,
		{
			//we have strdup'ed the event name
			free(p->first);
			p->first = NULL;
		});*/
		{
			t_pair * *_cur_11 = (*(t_pair * **)((void *)man->events + sizeof(t_object) + sizeof(size_t)));
			for (t_pair *  p = *_cur_11;
					_cur_11 != ((*(t_pair * **)((void *)man->events + sizeof(t_object) + sizeof(size_t))) + *((size_t *)(((void *)man->events) + sizeof(t_object))));
					p = *(++_cur_11)) {
				//we have strdup'ed the event name
				free(p->first);
				p->first = ((void *)0);
			}
		}
	}
}

int	str_compar(const void *a, const void *b)
{
	if (!a || !b)
		return (-1);
	return (strcmp((char *)a, (char *)b));
}

t_event_manager			*t_event_manager_new(t_event_manager_init var)
{
#ifdef	EVENT_SINGLETON
	static t_event_manager	*em = NULL;

	if (em != NULL)
		return (em);
#else
	t_event_manager		*em;
#endif
	if ((em = newObject(t_event_manager, t_event_delete)) == NULL ||
			(em->events = new(t_map, str_compar)) == NULL)
		return (NULL);
	if ((em->events_raised = new(t_list)) == NULL)
		return (NULL);
	em->is_direct = var.direct;
	return (em);
}

static int	_attach_handler(t_event_manager *em, const char *event_name,
		const t_event_handler handler)
{
	t_list	*l;

	if (!em || !event_name || !handler)
		return (EM_PARAM);
	if ((l = MGET(t_list *, em->events, event_name)) == NULL)
	{
		if ((l = new(t_list)) == NULL)
			return (EM_NOMEM);
		map_add(em->events, strdup(event_name), l);
	}
	if (LPUT(l, handler, 0) != LIST_NOERR)
		return (EM_NOMEM);
	return (EM_NOERR);
}

static int	_detach_handler(t_event_manager *em, const char *event_name,
		const t_event_handler handler)
{
	t_list	*l;
	size_t	idx;
	char		*tmp;

	if (!em || !event_name || !handler)
		return (EM_PARAM);
	if ((l = MGET(t_list *, em->events, event_name)) == NULL)
		return (EM_NOERR);
	if ((idx = list_search_index(l, handler)) == (size_t)-1)
		return (EM_NOERR);
	LPOP(l, idx);
	if (l->size == 0)
	{
		FOREACH(t_pair *, p, em->events,
			{
			//we have strdup'ed the event name
			if (!em->events->compar(p->first, event_name)) {
				tmp = p->first;
				break;
			}
		});
		map_remove(em->events, event_name);
		free(tmp);
	}
	return (EM_NOERR);
}

static void	_process_events(t_event_manager *em)
{
	t_pair	*act;

	if (!em)
		return ;
	while (em->events_raised->size > 0)
	{
		act = LGET(t_pair *, em->events_raised, 0);
		FOREACH(t_event_handler, func, act->first,
				func((t_event_args *)act->second););
		LPOP(em->events_raised, 0);
		delete(act);
	}
}

static int	_raise_event(t_event_manager *em, const char *event_name,
		const t_event_args args)
{
	t_list	*l;
	t_pair	*p;

	if (!em || !event_name)
		return (EM_PARAM);
	if ((l = MGET(t_list *, em->events, event_name)) == NULL)
		return (EM_NOERR);
	p = new(t_pair, list_clone(l), args);
	// Push the event at the end of the list
	if (LPUT(em->events_raised, p, em->events_raised->size) != LIST_NOERR)
		return (EM_NOMEM);
	if (em->is_direct)
		_process_events(em);
	return (EM_NOERR);
}

#ifdef EVENT_SINGLETON

int	attach_handler(const char *event_name, const t_event_handler handler)
{
	return (_attach_handler(new(t_event_manager), event_name, handler));
}

int	detach_handler(const char *event_name, const t_event_handler handler)
{
	return (_detach_handler(new(t_event_manager), event_name, handler));
}

int	raise_event(const char *event_name, const t_event_args args)
{
	return (_raise_event(new(t_event_manager), event_name, args));
}

void	process_events()
{
	t_event_manager *em;

	if ((em = new(t_event_manager)) == NULL)
		return ;
	if (em->is_direct)
		fprintf(stderr, "Warning: calling process_event() is useless if event_manager is in direct mode.\n");
	_process_events(em);
}

#else

int	attach_handler(t_event_manager *em, const char *event_name,
		const t_event_handler handler)
{
	return (_attach_handler(em, event_name, handler));
}

int	detach_handler(t_event_manager *em, const char *event_name,
		const t_event_handler handler)
{
	return (_detach_handler(em, event_name, handler));
}

int	raise_event(t_event_manager *em, const char *event_name,
		const t_event_args args)
{
	return (_raise_event(em, event_name, args));
}

void	process_events(t_event_manager *em)
{
	if (em && em->is_direct)
		fprintf(stderr, "Warning: calling process_event() is useless if event_manager is in direct mode.\n");
	_process_events(em);
}

#endif
