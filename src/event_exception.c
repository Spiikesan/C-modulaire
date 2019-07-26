#include "event_exception.h"
#include <stdlib.h>

static void EventException_del(t_object *this)
{
  EventException *self = this;

  self->ex = NULL;
}

EventException	*EventException_new(__attribute__((unused))EventException_init var)
{
  EventException *self;

  if ((self = newObject(EventException, EventException_del)) == NULL)
    return (NULL);
  self->ex = NULL;
  return (self);
}
