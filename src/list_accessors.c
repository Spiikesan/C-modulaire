#include "list.h"

size_t	list_size(t_list *l)
{
  return (l->size);
}

void		*list_get(t_list *m, size_t index)
{
  if (!m || index >= m->size)
    return (NULL);
  return (m->array[index]);
}
