#ifndef EXCEPTION_H_
# define EXCEPTION_H_

#include "object.h"

/* Max number of backtrace (stack trace) */
/* compile with -rdynamic on elf-based binary systems to get symbols names*/
#define MAX_BT 20

# define Exception_DEFINITION	\
	Exception,					\
	(pChar, msg),				\
	(pChar, file),				\
	(uLong, line),				\
	(pChar, buffer),			\
	(pChar, stack)

CMETA_STRUCT_DEF(Exception_DEFINITION);

char const	*Exception_to_string(t_object *);

#endif /* !EXCEPTION_H_ */
