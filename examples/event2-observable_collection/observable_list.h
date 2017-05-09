#ifndef OBSERVABLE_LIST_H_
# define OBSERVABLE_LIST_H_

/*
** Malloc/free, size_t
*/
# include <stdlib.h>

/*
** héritage
*/
# include "list.h"

# include "event_manager.h"

/*
** Define de configuration
*/
# define OBSERVABLE_LIST_MAX_DIFF	LIST_MAX_DIFF

/*
** Defines de retours.
*/
# define OBSERVABLE_LIST_ARGS	LIST_ARGS
# define OBSERVABLE_LIST_FUNC	LIST_FUNC
# define OBSERVABLE_LIST_NOMORE	LIST_NOMORE
# define OBSERVABLE_LIST_NOERR	LIST_NOERR

# define OLGET(type, olist, idx) ((type)(observable_list_get(olist, idx)))
# define OLPUT(olist, elem, idx) (observable_list_add(olist, (void *)elem, idx))
# define OLPOP(olist, idx) (observable_list_remove(olist, idx))

typedef enum {
  OL_GET,
  OL_PUT,
  OL_POP
} observable_list_event_type;

/*
** Utilisé pour le new (initialisation).
*/
typedef	t_list_init	t_observable_list_init;

typedef struct s_observable_list
{
  t_list		list;
  t_event_manager	*em;
}	t_observable_list;

t_observable_list	*t_observable_list_new(t_observable_list_init var);

int	observable_list_add(t_observable_list *l, void *value, size_t index);
int	observable_list_remove(t_observable_list *l, size_t index);
void	*observable_list_get(const t_observable_list *l, const size_t index);

void	observable_list_attach(t_observable_list *l, observable_list_event_type type, t_event_handler handler);
void	observable_list_detach(t_observable_list *l, observable_list_event_type type, t_event_handler handler);

#endif /* !OBSERVABLE_LIST_H_ */
