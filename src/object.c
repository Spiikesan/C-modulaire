#include <stdlib.h>
#include <string.h>
#include "object.h"

static t_object	*new_front = NULL;

/*
** reg/unreg modified to have a linked list
** so that the first pushed element
** will be the first deleted by the
** GC, so even if it's delete elements
** himself, the GC will not double-delete
** them (they cannot be before the element)
*/
static void	_reg_object(t_object *obj)
{
  if (!obj)
    return ;
  if (new_front == NULL) {
    obj->next = obj;
    obj->prev = obj->next;
    new_front = obj;
  }else{
    obj->next = new_front->next;
    obj->prev = new_front;
    obj->next->prev = obj;
    obj->prev->next = obj;
    new_front = obj;
  }
}

static void	_unreg_object(t_object *obj)
{
  if (!obj)
    return ;
  if (obj->prev == obj && obj->next == obj) {
    new_front = NULL;
  } else {
    obj->prev->next = obj->next;
    obj->next->prev = obj->prev;
    if (new_front == obj)
      new_front = obj->next;
  }
}

static	void clean_at_exit()
{
  while (new_front)
    delete(new_front);
}

t_object	*t_object_new(t_object_init var)
{
  t_object	*new;
  static char	first = 1;

  if (!var.obj_size || var.type_magic == 0)
    return (NULL);
  if ((new = malloc(var.obj_size)) == NULL)
    return (NULL);
  memset(new, 0, var.obj_size);
  if (first)
    {
      atexit(clean_at_exit);
      first = 0;
    };
  new->magic.obj = OBJECT_MAGIC;
  new->magic.type = var.type_magic;
  new->meta = var.meta;
  new->del = var.del;
  new->to_str = var.str;
  new->next = NULL;
  new->prev = NULL;
  _reg_object(new);
  return (new);
}

void	_delete(t_object *obj)
{
  if (!obj)
    return ;
  if (obj->del)
    obj->del(obj);
  _unreg_object(obj);
  free(obj);
}

const char	*get_object_name(const t_object *o)
{
  if (!o || !o->meta || !o->meta->name)
    return ("Null");
  return (o->meta->name);
}

int	is_same_objects(const t_object *a, const t_object *b)
{
  if (!a || !b)
    return (-1);
  return (a == b || strcmp(get_object_name(a), get_object_name(b)) == 0);
}

const char	*object_to_string(const t_object *o)
{
  if (!o || !o->to_str)
    return (get_object_name(o));
  return (o->to_str(o));
}
