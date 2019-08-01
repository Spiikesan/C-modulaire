#include <stdio.h>
#include "event_manager.h"

#ifndef EVENT_SINGLETON
# warning "Dont forget to compile using the -DEVENT_SINGLETON !"
#endif

void	event_callback(t_event_args arg)
{
  printf("calling %s: args = %s\n", __FUNCTION__, (char *)arg);
}

void	event2_callback(t_event_args arg)
{
  printf("calling %s: args = %s\n", __FUNCTION__, (char *)arg);
}

int main()
{
  /* It's mandatory to call the new once, to init the "direct" behaviour */
  new(t_event_manager, .direct=0);

  printf("Attaching first_event to the event_callback function\n");
  attach_handler("first_event", event_callback);

  printf("Attaching second_event to the event2_callback function\n");
  attach_handler("second_event", event2_callback);

  printf("raising second_event\n");
  raise_event("second_event", "SECOND_EVENT - CALL 1");

  printf("raising first_event\n");
  raise_event("first_event", "FIRST_EVENT - CALL 1");

  printf("raising third_event\n");
  raise_event("third_event", "THIRD_EVENT - CALL 1");

  printf("Detaching first_event to the event_callback function\n");
  detach_handler("first_event", event_callback);

  printf("raising second_event\n");
  raise_event("second_event", "SECOND_EVENT - CALL 2");

  printf("raising first_event\n");
  raise_event("first_event", "FIRST_EVENT - CALL 2");

  printf("raising third_event\n");
  raise_event("third_event", "THIRD_EVENT - CALL 2");

  /* Need to call the process_event() function if the parameter "direct" is set to 0 (false) */

  printf("calling process_events()\n");
  process_events();

  return 0;
}
