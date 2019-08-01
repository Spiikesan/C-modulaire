#include <string.h>
#include "list.h"

static void	list_del(t_object *ptr)
{
  t_list	*l;

  if (!ptr)
    return ;
  l = (t_list *)ptr;
  free(l->array);
}

CMETA_STRUCT_BUILD(t_list_DEFINITION)
{
  t_list	*l = newObject(t_list, &list_del);

  if (l) {
	  args.size++;
	  l->array = malloc(sizeof(void *) * args.size);
	  if (l->array) {
		  memset(l->array, 0, sizeof(void *) * args.size);
		  l->alloc = args.size;
		  l->size = 0;
	  } else {
		  delete(l);
	  }
  }
  return (l);
}

int		list_add(t_list *l, void *value, size_t index)
{
  size_t	j;

  if (!l || index > l->size)
    return (LIST_ARGS);
  if (l->size >= l->alloc - 1)
    if ((l->array = realloc(l->array,
			    (++l->alloc) * sizeof(void *))) == NULL)
      return (LIST_FUNC);
  l->array[l->size] = NULL;
  for (j = l->size; j && j >= index; --j)
    l->array[j] = l->array[j - 1];
  l->array[index] = value;
  ++l->size;
  return (LIST_NOERR);
}

int		list_remove(t_list *l, size_t index)
{
  size_t	i;

  if (!l || index >= l->size)
    return (LIST_ARGS);
  if (!l->size)
    return (LIST_NOMORE);
  --l->size;
  for (i = index; i < l->size; ++i)
    l->array[i] = l->array[i + 1];
  if (((l->alloc - 1) - l->size) >= LIST_MAX_DIFF)
    {
      l->alloc = (l->size + 1);
      if ((l->array = realloc(l->array,
			      (l->alloc) * sizeof(void *))) == NULL)
	return (LIST_FUNC);
    }
  return (LIST_NOERR);
}

t_list		*list_clone(const t_list *l)
{
  t_list	*n;

  n = new(t_list, l->size);
  n->size = l->size;
  n->alloc = l->alloc;
  memcpy(n->array, l->array, l->size * sizeof(void *));
  return (n);
}
