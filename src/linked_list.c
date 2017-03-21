#include "linked_list.h"

static void _del_ll(void *ptr)
{
  t_linked_list	*self;

  if (!ptr)
    return ;
  self = (t_linked_list *)ptr;
  free(self->elem);
}

static inline t_ll_elem	*_make_elem(void *elem)
{
  t_ll_elem	*e;

  if ((e = malloc(sizeof(*e))) == NULL)
    return (NULL);
  e->elem = elem;
  e->next = e;
  e->prev = e;
  return (e);
}

/*
** Link element b in next of elem a
** b->next = a->next
** b->prev = a
** a->next = b
** b->next->prev = b
*/
static inline void	_link_elems(t_ll_elem *a, t_ll_elem *b)
{
  b->next = a->next;
  b->prev = a;
  a->next = b;
  b->next->prev = b;
}

static inline void	_unlink_elem(t_ll_elem *a)
{
  a->prev->next = a->next;
  a->next->prev = a->prev;
}

t_linked_list	*t_linked_list_new(t_linked_list_init var)
{
  t_linked_list	*l;

  if ((l = newObject(t_linked_list, _del_ll)) == NULL)
    return (NULL);
  l->elem = _make_elem(var.elem);
  if (var.other) {
    if (tll_merge_lists(l, var.other) == -1) {
      delete(l);
      return (NULL);
    }
  }
  return (l);
}

int	tll_add_elem(t_linked_list *l, void *elem)
{
  t_ll_elem	*e;

  if ((e = _make_elem(elem)) == NULL)
    return (-1);
  _link_elems(l->elem, e);
  return (0);
}

void	*tll_rem_elem(t_linked_list *l, void *elem, int (*comp)(void *a, void *b))
{
  t_ll_elem	*e;
  void		*f;

  for (e = l->elem->next; e != l->elem; e = e->next) {
    if (comp(e->elem, elem) == 0) {
      break;
    }
  }
  if (comp(e->elem, elem) != 0)
    return (NULL);
  f = e->elem;
  _unlink_elem(e);
  free(e);
  return (f);
}

void	*tll_get_elem(t_linked_list *l, void *elem, int (*comp)(void *a, void *b))
{
  t_ll_elem	*e;

  for (e = l->elem->next; e != l->elem; e = e->next) {
    if (comp(e->elem, elem) == 0) {
      return (e->elem);
    }
  }
  if (comp(e->elem, elem) == 0)
    return (e->elem);
  return (NULL);
}

int	tll_merge_lists(t_linked_list *la, t_linked_list *lb)
{
  (void)la;
  (void)lb;
  return (0);
}
