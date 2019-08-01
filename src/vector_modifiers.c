#include "vector.h"

static void		vec_del(t_object *ptr)
{
  t_vector	*v;

  if (!ptr)
    return ;
  v = (t_vector *)ptr;
  free(v->array);
}

CMETA_STRUCT_BUILD(t_vector_DEFINITION)
{
  t_vector	*v = newObject(t_vector, &vec_del);

  if (v) {
	  ++args.size;
	  v->array = malloc(sizeof(void *) * args.size);
	  if (v->array) {
		  memset(v->array, 0, args.size * sizeof(void *));
		  v->alloc = args.size;
		  v->size = 0;
	  } else
		  delete(v);
  }
  return (v);
}

int	vector_push_back(t_vector *v, void *elem)
{
  if (!v)
    return (VEC_ARGS);
  if (v->size >= (v->alloc - 1))
    {
      if ((v->array = realloc(v->array,
			      (++v->alloc) * sizeof(void *))) == NULL)
	return (VEC_FUNC);
    }
  v->array[v->size] = elem;
  ++(v->size);
  return (VEC_NOERR);
}

int	vector_pop_back(t_vector *v)
{
  if (!v)
    return (VEC_ARGS);
  if (v->size == 0 || v->alloc == 1)
    return (VEC_NOMORE);
  --v->size;
  if (((v->alloc - 1) - v->size) >= VEC_MAX_DIFF)
    {
      v->alloc = v->size + 1;
      if ((v->array = realloc(v->array,
			      (v->alloc) * sizeof(void *))) == NULL)
	return (VEC_FUNC);
    }
  return (VEC_NOERR);
}

int	vector_set(t_vector *v, size_t index, void *elem)
{
  if (!v || index >= v->size)
    return (VEC_ARGS);
  v->array[index] = elem;
  return (VEC_NOERR);
}
