#include <stdio.h>
#include "my_string_event.h"
#include "event_manager.h"

#ifndef EVENT_SINGLETON
# warning "Dont forget to compile using the -DEVENT_SINGLETON !"
#endif

void	push_all_events()
{
  push_event((t_event *)new(string_event, "evenement 1"));
  push_event((t_event *)new(string_event, "evenement 2"));
  push_event((t_event *)new(string_event, "evenement 3"));
  push_event((t_event *)new(string_event, "evenement 4"));
}

void	show_all_events()
{
  printf("There is %lu available events.\nGetting first event...\n", event_count());
  while (print_string_event((string_event *)get_event()))
    printf("Getting the next event...\n");
}

int main()
{
  /* It's mandatory to call the new once, to init the events buffer size */
  new(t_event_manager, 5);

  push_all_events();
  show_all_events();
  return 0;
}
