#include <string.h>
#include <stdio.h>
#include "my_string_event.h"

void	string_event_del(void *ptr)
{
  string_event	*self;

  if ((self = ptr) == NULL)
    return ;
  free(self->str);
}

string_event	*string_event_new(string_event_init var)
{
  string_event	*e;

  if ((e = newObject(string_event, string_event_del)) == NULL)
    return (NULL);
  e->str = strdup(var.str);
  return (e);
}

int	print_string_event(string_event *ev)
{
  int	ret;

  ret = 0;
  if (ev && (ret = 1))
    printf("Event : '%s'\n", ev->str);
  else
    printf("No event.\n");
  delete(ev);
  return (ret);
}
