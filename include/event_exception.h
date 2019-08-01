#ifndef EVENT_EXCEPTION_H_
# define EVENT_EXCEPTION_H_

# include <setjmp.h>
# include "object.h"

# define EventException_DEFINITION\
	EventException, \
	(jmp_buf, buff),\
	(t_pobject, ex)

CMETA_STRUCT_DEF(EventException_DEFINITION);

#endif /* EVENT_EXCEPTION_H_ */
