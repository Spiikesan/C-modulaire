#ifndef EXCEPTION_HANDLER_H_
# define EXCEPTION_HANDLER_H_

# include <stdio.h>
# include <setjmp.h>
# include "object.h"
# include "list.h"
# include "event_exception.h"

#define JMP_BUFF_INIT	(jmp_buff)({{{0}, 0, {{0}}}})

/* Max number of levels of exceptions */
#define MAX_EX 10

# define ExceptionHandler_DEFINITION	\
	ExceptionHandler,			\
	(t_plist, tab)

CMETA_STRUCT_DEF(ExceptionHandler_DEFINITION);

jmp_buf			*ExceptionHandler_try(ExceptionHandler *this,
					      size_t id);
jmp_buf			*ExceptionHandler_throw(ExceptionHandler *this,
						size_t id, t_object *exception);
t_object		*ExceptionHandler_getEx(ExceptionHandler *this,
						size_t id);
ExceptionHandler	*getHandler();

/* try(int) -> The int is the id of the exception (begin at 1) */
#define try(z) do { switch( setjmp(*ExceptionHandler_try(getHandler(), z)) ) { case 0: while(1) {

/* catch(int) -> The int is the throw identifier (see the throw section) */
#define catch(x) break; case x:

/* Done at each time. Optional */
#define finally break; } default: {

/* Mandatory. End of the try */
#define etry break; } } } while(0)

/* throw(int, t_object *, int) -> The int is the id of the tryied exception. the object will be the one returned by the next macro, and the last int is the catch identifier*/
#define throw(x, y, z) longjmp(*ExceptionHandler_throw(getHandler(), x, (t_object *)y), z)

/* getEx(int) -> return the throwed t_object*. Used in the "catch" statement */
#define getEx(z) ExceptionHandler_getEx(getHandler(), z)

#endif /* !EXCEPTION_HANDLER_H_ */
