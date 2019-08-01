#include "linked_list.h"
#include <stdlib.h>

static void _del_ll(t_object *ptr)
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

CMETA_STRUCT_BUILD(t_linked_list_DEFINITION)
{
  t_linked_list	*l = newObject(t_linked_list, _del_ll);

  if (l) {
	  l->elem = args.elem;
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

void	*tll_rem_elem(t_linked_list *l, const void *elem, int (*comp)(const void *a, const void *b))
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

void	*tll_get_elem(t_linked_list *l, const void *elem, int (*comp)(const void *a, const void *b))
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

int	tll_merge_lists(t_linked_list *la, const t_linked_list *lb)
{
  t_ll_pelem e;

  for (e = lb->elem->next; e != lb->elem; e = e->next) {
      tll_add_elem(la, e->elem);
  }
  return (0);
}
