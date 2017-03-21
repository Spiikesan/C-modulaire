#ifndef EVENT_EXCEPTION_H_
# define EVENT_EXCEPTION_H_

# include <setjmp.h>
# include "new.h"

typedef struct	s_EventException
{
  t_object	__obj__;
  jmp_buf	buff;
  t_object	*ex;
}		EventException;

typedef struct	s_EventException_init
{

}		EventException_init;

EventException	*EventException_new(EventException_init var);

#endif /* EVENT_EXCEPTION_H_ */
