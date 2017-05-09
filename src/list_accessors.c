#include "list.h"

size_t	list_size(const t_list *l)
{
  return (l->size);
}

void		*list_get(const t_list *m, const size_t index)
{
  if (!m || index >= m->size)
    return (NULL);
  return (m->array[index]);
}

size_t		list_search_index(const t_list *m, const void *search)
{
  size_t	index;

  if (!m || !search)
    return (-1);
  for (index = 0; index < m->size; ++index)
    if (m->array[index] == search)
      return (index);
  return (-1);
}
