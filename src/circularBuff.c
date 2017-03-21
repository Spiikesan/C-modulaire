#include <string.h>
#include "circularBuff.h"

void			cb_del(void *ptr)
{
  t_circularBuff	*c;

  if (!ptr)
    return ;
  c = ptr;
  free(c->array);
}

t_circularBuff	*t_circularBuff_new(t_circularBuff_init var)
{
  t_circularBuff	*c;

  if (var.size == 0)
    return (NULL);
  if ((c = newObject(t_circularBuff, &cb_del)) == NULL)
    return (NULL);
  if ((c->array = malloc(sizeof(void *) * (var.size + 1))) == NULL)
    return (NULL);
  memset(c->array, 0, sizeof(void *) * (var.size + 1));
  c->size = var.size;
  c->alloc = var.size + 1;
  c->remain = var.size;
  c->read = 0;
  c->write = 0;
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
