#ifndef EVENT_MANAGER_H_
# define EVENT_MANAGER_H_

# include "object.h"
# include "map.h"
# include "list.h"

/*
** You have to compile with -DEVENT_SINGLETON to use the singleton feature
*/

# define EM_NOERR	(0)
# define EM_NOMEM	(-2)
# define EM_PARAM	(-1)

typedef void *t_event_args;
typedef void (*t_event_handler)(t_event_args args);

/*
** direct == true(1) => events are directly processed
** direct == false(0) => need to run process_events function
*/

/*
** This struct contains
** a map (index = event name) of vector of
** t_event_handler functions pointers.
** events_raised is a list of pairs
** first = t_list of callbacks,
** second = the t_event_args
*/
# define t_event_manager_DEFINITION \
		t_event_manager,			\
		(int,		direct),		\
		(t_pmap,	events),		\
		(t_plist,	events_raised)

CMETA_STRUCT_DEF(t_event_manager_DEFINITION);

typedef t_event_manager *t_pevent_manager;

# ifdef EVENT_SINGLETON

int		attach_handler(const char *event_name, t_event_handler handler);
int		detach_handler(const char *event_name, t_event_handler handler);
int		raise_event(const char *event_name, t_event_args args);
void		process_events();

# else

int		attach_handler(t_event_manager *em, const char *event_name,
			       t_event_handler handler);
int		detach_handler(t_event_manager *em, const char *event_name,
			       t_event_handler handler);
int		raise_event(t_event_manager *em, const char *event_name,
			    t_event_args args);
void		process_events(t_event_manager *em);

# endif

#endif /* !EVENT_MANAGER_H_ */
