#ifndef LINKED_LIST_H_
# define LINKED_LIST_H_

# include "object.h"

typedef struct s_ll_elem	*t_ll_pelem;

# define MAGIC_t_linked_list DEFAULT_MAGIC

typedef struct	s_ll_elem
{
	struct s_ll_elem	*next;
	struct s_ll_elem	*prev;
	Pointer				elem;
}			t_ll_elem;

# define t_linked_list_DEFINITION	\
	t_linked_list,					\
	(t_ll_pelem, elem)

CMETA_STRUCT_DEF(t_linked_list_DEFINITION);

/**
 * Add a list B nodes to list A. If a list B note already exists (the node pointer, not it's value) then element is ignored.
 */
int	tll_merge_lists(t_linked_list *la, const t_linked_list *lb);
int	tll_add_elem(t_linked_list *l, void *elem);
void	*tll_get_elem(t_linked_list *l, const void *elem, int (*comp)(const void *a, const void *b));
void	*tll_rem_elem(t_linked_list *l, const void *elem, int (*comp)(const void *a, const void *b));

#endif /* !LINKED_LIST_H_ */
