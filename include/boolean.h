#ifndef BOOLEAN_H_
# define BOOLEAN_H_

/**
 * Boolean representation for functional use
 */

# include "varargs.h"
# include "new.h"

typedef struct boolean_s *Boolean;

# define MAGIC_t_boolean DEFAULT_MAGIC

typedef Boolean (*boolean_func_b)(Boolean);
typedef Boolean (*boolean_func_v)();

typedef Boolean (*boolean_funcparam)(varargs);
typedef Boolean (*boolean_func_f)(boolean_funcparam, varargs);

struct          boolean_s
{
	const t_object          __obj__;
    const int               value;
    const char              *valueStr;
    const boolean_func_b    and;
    const boolean_func_b    or;
    const boolean_func_v    not;
    const boolean_func_b    xor;
    const boolean_func_f    ifTrue;
    const boolean_func_f    ifFalse;
};

extern const Boolean const True;

extern const Boolean const False;

#endif /* !BOOLEAN_H_ */
