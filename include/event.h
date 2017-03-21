#ifndef EVENT_H_
# define EVENT_H_

/*
** You have to inherits from that struct to get a
** functionnal event system.
** example :
** struct event_test
** {
**   t_event	__event__;
**   ...
**   ... what_you_want
**   ...
** }
**
*/

/* typedef struct	s_event_init */
/* { */
/* }		t_event_init; */

typedef struct	s_event
{
  t_object	__obj__;
}		t_event;

#endif /* !EVENT_H_ */
