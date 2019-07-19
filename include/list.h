#ifndef LIST_H_
# define LIST_H_

/*
** Malloc/free, size_t
*/
# include <stdlib.h>

/*
** new/delete
*/
# include "new.h"

/*
** Define de configuration
*/
# define LIST_MAX_DIFF	(8)

# define MAGIC_t_list DEFAULT_MAGIC

/*
** Defines de retours.
*/
# define LIST_ARGS	(-1)
# define LIST_FUNC	(-2)
# define LIST_NOMORE	(-3)
# define LIST_NOERR	(0)

# define LGET(type, list, idx) ((type)(list_get(list, idx)))
# define LPUT(list, elem, idx) (list_add(list, (void *)elem, idx))
# define LPOP(list, idx) (list_remove(list, idx))

/*
** Utilisé pour le new (initialisation).
*/
typedef struct	s_list_init
{
  size_t	size;
}		t_list_init;

typedef struct	s_list
{
  t_object	__obj__;
  size_t	size;
  void		**array;
  size_t	alloc;
}		t_list;

t_list	*t_list_new(t_list_init var);
void	list_del(void *ptr);
size_t	list_size(const t_list *l);
int	list_add(t_list *l, void *value, size_t index);
int	list_remove(t_list *l, size_t index);
size_t	list_search_index(const t_list *m, const void *search);
void	*list_get(const t_list *l, const size_t index);
t_list	*list_clone(const t_list *l);

#endif /* !LIST_H_ */
