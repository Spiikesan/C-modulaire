#include "observable_list.h"

void		*observable_list_get(const t_observable_list *l, const size_t index)
{
  raise_event(l->em, "get", (t_event_args)&index);
  return (list_get((t_list *)l, index));
}
