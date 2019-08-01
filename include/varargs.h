#ifndef VARARGS_H_
# define VARARGS_H_

# include "object.h"

# define MAX_ARGS (10)

# define MAGIC_t_varargs DEFAULT_MAGIC

enum type_e {
    TYPE_E_INT = 0,
    TYPE_E_PINT,
    TYPE_E_LONG_INT,
    TYPE_E_PLONG_INT,
    TYPE_E_DOUBLE,
    TYPE_E_PDOUBLE,
    TYPE_E_PTR,
    TYPE_E_STR,
    TYPE_E_PSTR,
    TYPE_E_BOOLEAN,
    TYPE_E_PBOOLEAN,
    TYPE_E_COUNT
};

struct boolean_s;

/**
 * Get the numerical value of the segment "seg" and put it in the container "cont"
 * The value is cast with the type of "cont".
 * May be I will parse number if it's a string, maybe not. Will see later.
 */
# define VARARG_GET_NUMBER(seg, cont)                                                        \
    switch ((seg)._type) {                                                              \
    case TYPE_E_INT: (cont) = (typeof(cont))(seg)._value.type_int; break;               \
    case TYPE_E_PINT: (cont) = (typeof(cont))*(seg)._value.type_pint; break;            \
    case TYPE_E_LONG_INT: (cont) = (typeof(cont))(seg)._value.type_long_int; break;     \
    case TYPE_E_PLONG_INT: (cont) = (typeof(cont))*(seg)._value.type_plong_int; break;  \
    case TYPE_E_DOUBLE: (cont) = (typeof(cont))(seg)._value.type_double; break;         \
    case TYPE_E_PDOUBLE: (cont) = (typeof(cont))*(seg)._value.type_pdouble; break;      \
    case TYPE_E_BOOLEAN: (cont) = (typeof(cont))(seg)._value.type_bool->value; break;   \
    case TYPE_E_PBOOLEAN: (cont) = (typeof(cont))(*(seg)._value.type_pbool)->value; break;\
    default: break;                                                                     \
    }

typedef union type_u
{
    int type_int, *type_pint;
    long int type_long_int, *type_plong_int;
    double type_double, *type_pdouble;
    void *type_ptr;
    char *type_str, **type_pstr;
    struct boolean_s *type_bool, **type_pbool;
}		type_u_array[MAX_ARGS];

typedef struct s_segment
{
       enum type_e _type;
       union type_u _value;
}				t_segment_array[MAX_ARGS];

# define t_varargs_DEFINITON	\
	t_varargs,					\
	(pChar, fmt),				\
	(type_u_array, values),		\
	(uInt, count),				\
	(t_segment_array, segments)

CMETA_STRUCT_DEF(t_varargs_DEFINITON);

typedef t_varargs *varargs;

/**
 * Idem, but use the provided arg, that will be erased.
 */
varargs varargs_create_fromVar(t_varargs *args, char *fmt, ...);

/**
 * Push an argument of the specified type into the list.
 * Returns 0 if the argument is not pushed, else the current count
 * of arguments.
 */
int varargs_add(varargs args, enum type_e type, union type_u value);

/**
 * Circular Inclusion
 */
# include "Boolean.h"

#endif /* !VARARGS_H_ */
