#include "exception_handler.h"
#include "raise.h"

static void ExceptionHandler_del(void *self)
{
  ExceptionHandler *this = self;
  this->tab = NULL;
}

ExceptionHandler	*ExceptionHandler_new(__attribute__((unused)) ExceptionHandler_init var)
{
  ExceptionHandler	*this;
  int			i;

  if ((this = newObject(ExceptionHandler, &ExceptionHandler_del)) == NULL)
    return (NULL);
  if ((this->tab = new(t_list)) == NULL)
    return (NULL);
  for (i = 0; i < MAX_EX; ++i)
    LPUT(this->tab, new(EventException), 0);
  return (this);
}

jmp_buf	*ExceptionHandler_try(ExceptionHandler *this, size_t id)
{
  if (id > this->tab->size)
    raise("try : Id out of range");
  EventException *event = LGET(EventException *, this->tab, id);
  if (!event)
    raise("try : Cannot get requested exception event id");
  /* setitem(this->tab, id, new(EventException)); */
  /* event = getitem(this->tab, id); */
  return (&event->buff);
}

jmp_buf	*ExceptionHandler_throw(ExceptionHandler *this, size_t id, t_object *exception)
{
  if (id > this->tab->size)
    raise("throw : Id out of range");
  EventException *event = LGET(EventException *, this->tab, id);
  if (!event)
    raise("throw : Cannot get requested exception event id");
  event->ex = exception;
  return (&event->buff);
}

t_object	*ExceptionHandler_getEx(ExceptionHandler *this, size_t id)
{
  if (id > this->tab->size)
    raise("getEx : Id out of range");
  EventException *event = LGET(EventException *, this->tab, id);
  if (!event)
    raise("getEx : Cannot get requested event id");
  return (event->ex);
}

ExceptionHandler *getHandler()
{
  static ExceptionHandler *handler = NULL;

  if (handler == NULL)
    if ((handler = new(ExceptionHandler)) == NULL)
      raise("getHandler : Cannot allocate memory");
  return (handler);
}
