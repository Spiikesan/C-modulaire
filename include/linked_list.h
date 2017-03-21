#ifndef LINKED_LIST_H_
# define LINKED_LIST_H_

# include "new.h"

typedef struct	s_ll_elem	t_ll_elem;

struct		s_ll_elem
{
  t_ll_elem	*next;
  t_ll_elem	*prev;
  void		*elem;
};

typedef struct	s_linked_list
{
  t_object	__obj__;
  t_ll_elem	*elem;
}		t_linked_list;

typedef struct	s_linked_list_init
{
  void		*elem;
  t_linked_list	*other;
}		t_linked_list_init;

t_linked_list		*t_linked_list_new(t_linked_list_init var);

int	tll_merge_lists(t_linked_list *la, t_linked_list *lb);
int	tll_add_elem(t_linked_list *l, void *elem);
void	*tll_get_elem(t_linked_list *l, void *elem, int (*comp)(void *a, void *b));
void	*tll_rem_elem(t_linked_list *l, void *elem, int (*comp)(void *a, void *b));

#endif /* !LINKED_LIST_H_ */
