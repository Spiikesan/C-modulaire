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

# define MAGIC_t_observable_list DEFAULT_MAGIC

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

# define t_observable_list_DEFINITION	\
	t_observable_list,					\
	(t_plist, list),					\
	(t_pevent_manager, em)

CMETA_STRUCT_DEF(t_observable_list_DEFINITION);

int	observable_list_add(t_observable_list *l, void *value, size_t index);
int	observable_list_remove(t_observable_list *l, size_t index);
void	*observable_list_get(const t_observable_list *l, const size_t index);

void	observable_list_attach(t_observable_list *l, observable_list_event_type type, t_event_handler handler);
void	observable_list_detach(t_observable_list *l, observable_list_event_type type, t_event_handler handler);

#endif /* !OBSERVABLE_LIST_H_ */
