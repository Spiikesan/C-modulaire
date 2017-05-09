#include <string.h>
#include "observable_list.h"

static void	observable_list_del(void *ptr)
{
  t_observable_list	*l;

  if (!ptr)
    return ;
  l = ptr;
  free(l->list.array);
}

t_observable_list	*t_observable_list_new(t_observable_list_init var)
{
  t_observable_list	*l;

  if ((l = newObject(t_observable_list, &observable_list_del)) == NULL)
    return (NULL);
  ++var.size;
  if ((l->list.array = malloc(sizeof(void *) * var.size)) == NULL ||
      (l->em = new(t_event_manager, 1)) == NULL)
    return (NULL);
  memset(l->list.array, 0, sizeof(void *) * var.size);
  l->list.alloc = var.size;
  l->list.size = 0;
  return (l);
}

int		observable_list_add(t_observable_list *l, void *value, size_t index)
{
  t_pair	*p;

  p = new(t_pair, value, &index);
  raise_event(l->em, "add", (t_event_args)p);
  delete(p);
  return (list_add((t_list *)l, value, index));
}

int		observable_list_remove(t_observable_list *l, size_t index)
{
  raise_event(l->em, "remove", (t_event_args)&index);
  return (list_remove((t_list *)l, index));
}
