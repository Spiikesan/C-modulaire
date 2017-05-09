#include "observable_list.h"

void	observable_list_attach(t_observable_list *l, observable_list_event_type type, t_event_handler handler)
{
  if (!l || !handler)
    return ;
  switch (type)
    {
    case OL_GET:
      attach_handler(l->em, "get", handler);
      break;
    case OL_PUT:
      attach_handler(l->em, "add", handler);
      break;
    case OL_POP:
      attach_handler(l->em, "remove", handler);
      break;
    default:
      break;
    }
}

void	observable_list_detach(t_observable_list *l, observable_list_event_type type, t_event_handler handler)
{
  if (!l || !handler)
    return ;
  switch (type)
    {
    case OL_GET:
      detach_handler(l->em, "get", handler);
      break;
    case OL_PUT:
      detach_handler(l->em, "add", handler);
      break;
    case OL_POP:
      detach_handler(l->em, "remove", handler);
      break;
    default:
      break;
    }
}
