#ifndef MY_STRING_EVENT_H_
# define MY_STRING_EVENT_H_

# include "new.h"
# include "event.h"

typedef struct	string_event_init
{
  char		*str;
}		string_event_init;

typedef struct	string_event
{
  t_event	__event__;
  char		*str;
}		string_event;

string_event	*string_event_new(string_event_init var);

int	print_string_event(string_event *ev);

#endif /* MY_STRING_EVENT_H_ */
