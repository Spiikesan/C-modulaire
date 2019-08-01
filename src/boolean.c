#include "boolean.h"

static const char *bool_str(const t_object *o);

static Boolean true_and(Boolean val);
static Boolean true_or(Boolean val);
static Boolean true_not();
static Boolean true_xor(Boolean val);
static Boolean true_ifTrue(boolean_funcparam, varargs);
static Boolean true_ifFalse(boolean_funcparam, varargs);

static Boolean false_and(Boolean val);
static Boolean false_or(Boolean val);
static Boolean false_not();
static Boolean false_xor(Boolean val);
static Boolean false_ifTrue(boolean_funcparam, varargs);
static Boolean false_ifFalse(boolean_funcparam, varargs);

static struct boolean_s true_def = {
		{{OBJECT_MAGIC, 0x10000000}, 0, 0, 0, 0, &bool_str},
        1,
        "True",
        &true_and,
        &true_or,
        &true_not,
        &true_xor,
        &true_ifTrue,
        &true_ifFalse
};

static struct boolean_s false_def = {
		{{OBJECT_MAGIC, 0x10000000}, 0, 0, 0, 0, &bool_str},
        0,
        "False",
        &false_and,
        &false_or,
        &false_not,
        &false_xor,
        &false_ifTrue,
        &false_ifFalse
};

const Boolean const True = &true_def;

const Boolean const False = &false_def;

static const char *bool_str(__attribute__((unused)) const t_object *o)
{
	return "Boolean";
}

static Boolean true_and(Boolean val)
{
    return val;
}

static Boolean true_or(__attribute__((unused)) Boolean val)
{
    return True;
}

static Boolean true_not()
{
    return False;
}

static Boolean true_xor(Boolean val)
{
    return val->not();
}

static Boolean true_ifTrue(boolean_funcparam func, varargs argp)
{
    return func(argp);
}

static Boolean true_ifFalse(__attribute__((unused)) boolean_funcparam func, __attribute__((unused)) varargs argp)
{
    return False;
}

static Boolean false_and(__attribute__((unused)) Boolean val)
{
    return False;
}

static Boolean false_or(Boolean val)
{
    return val;
}

static Boolean false_not()
{
    return True;
}

static Boolean false_xor(Boolean val)
{
    return val;
}

static Boolean false_ifTrue(__attribute__((unused)) boolean_funcparam func, __attribute__((unused))varargs argp)
{
    return False;
}

static Boolean false_ifFalse(boolean_funcparam func, varargs argp)
{
    return func(argp);
}
