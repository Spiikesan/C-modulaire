#include "map.h"

size_t	map_size(t_map *m)
{
  return (m->size);
}

void		*map_get(t_map *m, void *key)
{
  size_t	i;

  for (i = 0; i < m->size; ++i)
    {
      if (m->array[i] && !m->compar(key, m->array[i]->first))
	return (m->array[i]->second);
    }
  return (m->defVal);
}
