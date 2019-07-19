#ifndef EXCEPTION_H_
# define EXCEPTION_H_

#include "new.h"

/* Max number of backtrace (stack trace) */
/* compile with -rdynamic to get the symbols names*/
#define MAX_BT 200

# define MAGIC_Exception DEFAULT_MAGIC

typedef struct	s_Exception
{
  t_object	base;
  char		*buffer;
  char		*msg;
  char		*file;
  size_t	line;
  char		*stack;
}		Exception;

typedef struct	s_Exception_init
{
  char		*msg;
  char		*file;
  size_t	line;
}		Exception_init;

Exception	*Exception_new(Exception_init var);
char const	*Exception_to_string(t_object *);

#endif /* !EXCEPTION_H_ */
