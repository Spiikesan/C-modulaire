#include <string.h>
#include "circularBuff.h"

static void cb_del(t_object *ptr)
{
  t_circularBuff	*c;

  if (!ptr)
    return ;
  c = (t_circularBuff*) ptr;
  free(c->array);
}

CMETA_STRUCT_BUILD(t_circularBuff_DEFINITION)
{
  t_circularBuff	*c = newObject(t_circularBuff, &cb_del);

  if (c) {
	  if (args.size > 0) {
		  c->array = malloc(sizeof(void *) * (args.size + 1));
		  if (c->array) {
			  memset(c->array, 0, sizeof(void *) * (args.size + 1));
			  c->size = args.size;
			  c->alloc = args.size + 1;
			  c->remain = args.size;
			  c->read = 0;
			  c->write = 0;
		  } else
			  delete(c);
	  } else
		  delete(c);
  }
  return (c);
}

int	circularBuff_put(t_circularBuff *c, void *elem)
{
  if (!c || ((c->write + 1) % c->alloc) == c->read)
    return (CBF_NOPLACE);
  --c->remain;
  c->array[(c->write = (c->write + 1) % c->alloc)] = elem;
  return (CBF_NOERR);
}

void	*circularBuff_get(t_circularBuff *c)
{
  void	*ret;

  if (!c || c->read == c->write)
    return (NULL);
  ++c->remain;
  c->read = (c->read + 1) % c->alloc;
  ret = c->array[c->read];
  c->array[c->read] = NULL;
    return (ret);
}

size_t		circularBuff_remain(t_circularBuff *v)
{
  if (!v)
    return (0);
  return (v->remain);
}
