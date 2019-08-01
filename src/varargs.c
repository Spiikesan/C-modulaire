#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "varargs.h"

static inline union type_u _nativeType_getValue(va_list *vl, enum type_e type, __attribute__((unused))int ptr)
{
    switch (type) {
    case TYPE_E_INT: return (union type_u)va_arg(*vl, int);
    case TYPE_E_PINT: return (union type_u)va_arg(*vl, int *);
    case TYPE_E_LONG_INT: return (union type_u)va_arg(*vl, long int);
    case TYPE_E_PLONG_INT: return (union type_u)va_arg(*vl, long int *);
    case TYPE_E_DOUBLE: return (union type_u)va_arg(*vl, double);
    case TYPE_E_PDOUBLE: return (union type_u)va_arg(*vl, double *);
    case TYPE_E_PTR: return (union type_u)va_arg(*vl, void *);
    case TYPE_E_STR: return (union type_u)va_arg(*vl, char *);
    case TYPE_E_PSTR: return (union type_u)va_arg(*vl, char **);
    case TYPE_E_BOOLEAN: return (union type_u)va_arg(*vl, Boolean);
    case TYPE_E_PBOOLEAN: return (union type_u)va_arg(*vl, Boolean *);
    default: return (union type_u)((void *)(0));
    }
}

static void _varargs_build(varargs args, char *fmt, va_list *vl, union type_u *values) {
    int i = 0, j = 0;
    int ptr = 0;
    int count = 1;
    enum type_e type = TYPE_E_COUNT;
    int done = 0;
    static struct {
        int c;
        enum type_e type;
    } assoc[TYPE_E_COUNT] = {
            {'i', TYPE_E_INT},
            {'\1', TYPE_E_PINT}, //Unused. Use "pi" instead.
            {'l', TYPE_E_LONG_INT},
            {'\1', TYPE_E_PLONG_INT}, //Unused. Use "pl" instead.
            {'d', TYPE_E_DOUBLE},
            {'\1', TYPE_E_PDOUBLE}, //Unused. Use "pd" instead.
            {'p', TYPE_E_PTR},
            {'s', TYPE_E_STR},
            {'\1', TYPE_E_PSTR}, //Unused. Use "ps" instead.
            {'b', TYPE_E_BOOLEAN},   //Extension
            {'\1', TYPE_E_PBOOLEAN}, //Unused. Use "pb" instead.
    };

    memset(args, 0, sizeof(*args));
    while (*fmt && !done) {
        if (*fmt != ';') {
            for (i = 0; i < TYPE_E_COUNT; i++) {
                if (*fmt == assoc[i].c) {
                    type = assoc[i].type + ptr;
                    break;
                }
            }
            if (type == TYPE_E_PTR)
                ptr = 1;
            if (type == TYPE_E_COUNT)
            {
                if (isdigit(*fmt) && *fmt != '0') {
                    count = *fmt++ - '0';
                    while (isdigit(*fmt)) {
                        count *= 10;
                        count += *fmt++ - '0';
                    }
                    fmt--;
                }
            }
        } else {
            if (type != TYPE_E_COUNT) {
                while (*fmt != 0 && count-- >0) {
                	if (vl) {
                		if (!varargs_add(args, type, _nativeType_getValue(vl, type, ptr)))
                			done = 1;
                	} else if (values) {
                		if (!varargs_add(args, type, values[j++]))
                		    done = 1;
                	} else {
                		done = 1;
                	}
                }
                ptr = 0;
                count = 1;
                type = TYPE_E_COUNT;
            }
        }
        fmt++;
    }
}

CMETA_STRUCT_BUILD(t_varargs_DEFINITON)
CMETA_DEFAULT_BUILD(t_varargs_DEFINITON)

varargs varargs_create_fromVar(varargs args, char *fmt, ...)
{
    va_list vl;
    if (!args || !fmt)
        return NULL;
    va_start(vl, fmt);
    _varargs_build(args, fmt, &vl, NULL);
    va_end(vl);
    return args;
}

int varargs_add(varargs args, enum type_e type, union type_u value)
{
    if (!args || args->count >= MAX_ARGS)
        return 0;
    args->segments[args->count]._type = type;
    args->segments[args->count]._value = value;
    return ++args->count;
}
