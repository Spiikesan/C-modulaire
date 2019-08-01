#include <string.h>
#include "observable_list.h"

static void	observable_list_del(t_object *ptr)
{
  t_observable_list	*l;

  if (!ptr)
    return ;
  l = (t_observable_list *)ptr;
  delete(l->list);
  delete(l->em);
}

CMETA_STRUCT_BUILD(t_observable_list_DEFINITION)
{
  t_observable_list	*l = newObject(t_observable_list, &observable_list_del);

  (void)args;
  if (l) {
	  l->list = new(t_list);
	  if (l->list) {
	        l->em = new(t_event_manager, .direct=1);
	        if (!l->em)
	        	delete(l);
	  } else
		  delete(l);
  }
  return (l);
}

int		observable_list_add(t_observable_list *l, void *value, size_t index)
{
  t_pair	*p;

  p = new(t_pair, value, &index);
  raise_event(l->em, "add", (t_event_args)p);
  delete(p);
  return (list_add(l->list, value, index));
}

int		observable_list_remove(t_observable_list *l, size_t index)
{
  raise_event(l->em, "remove", (t_event_args)&index);
  return (list_remove(l->list, index));
}
