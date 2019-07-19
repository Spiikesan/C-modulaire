#ifndef _CMETA_H_
# define _CMETA_H_

# include <stddef.h>
# include "new.h"

/**
 * Defines a structure containing metadata.
 *
 * Designed to be used with a macro :
 *
 * #define MY_STRUCT_DEF my_struct_t, (type, memname)
 *
 * The combination ", (type, memname)" can be extended up to 8 individual members, where 'type' are C types and 'memname' are the members names.
 *
 * Then, you have to call the following macro IN A .H to build the definition of the structure wich
 * contain a pointer to the meta structure :
 *
 * Currently unsupported features :
 *  - fixed arrays declared with '[' _num_ ']'.
 *  - function pointers.
 */
#define CMETA_STRUCT_DEF(...) CMETA_STRUCT_DEF_(__VA_ARGS__)

/**
 * You must include this magic number to your own to let the CMeta library
 * recognize your object.
 * For example :
 * #define MAGIC_myType (CMETA_MAGIC + DEFAULT_MAGIC)
 */
#define CMETA_MAGIC (0xFECA0000U)
#define MAGIC_myType (CMETA_MAGIC + DEFAULT_MAGIC)
/*
 * get the meta structure name
 */
#define CMETA(type) CMETA1(type)
#define CMETA1(type) cmeta_##type

#define STRINGIZE(arg)  STRINGIZE1(arg)
#define STRINGIZE1(arg) STRINGIZE2(arg)
#define STRINGIZE2(arg) #arg

#define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
#define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
#define CONCATENATE2(arg1, arg2)  arg1##arg2

/**
 * You must call this macro with the previous #define MY_STRUCT_DEF as parameter IN A .C file to build the constant metadata structure.
 */
#define CMETA_STRUCT_BUILD(...) CMETA_STRUCT_BUILD_(__VA_ARGS__)

/**
 * Init metadata structure by assigning &CMETA(my_struct) to te meta member.
 */

/**
 * Add meta to the globally accessible symbol list.
 */
#define CMETA_ADDSYMBOL(name) cmeta_##name##_addSymbol();

/**
 * Read a value based on member name
 * Can give a pointer on a pointer of meta type struct to get meta informations on the type.
 * The meta struct pointer given indicates if the given member is the actual value returned
 * by the function.
 */
#define CMETA_READ(type, ptr, memname, metatype) cmeta_read_cmeta_##type(ptr, memname, metatype)

/**
 * Set a value based on the member name.
 * Return int value such as :
 * 0 - No error, the value is set.
 * 1 - Error, the member is not found
 * 2 - Error, the member don't have the given type
 * -1 - Error, a parameter is incorrect (NULL ptr/memname, or ptr not a cmeta compatible pointer)
 */
#define CMETA_SET(type, ptr, memname, value) cmeta_set_cmeta_##type(ptr, memname, value)

/**
 * Types.
 * You MUST use these types. For example, to use a char * in a struct,
 * you must set "pchar" as a type.
 * If you want to define your own, it must be a typedef, as it MUST be
 * a one-word type.
 */
#define CMETA_TYPE1(type, name, pname) typedef type name, *pname
#define CMETA_TYPE(type, name) CMETA_TYPE1(type, CMETA(name), CMETA(CONCATENATE(p, name)))

CMETA_TYPE(char,        char);
CMETA_TYPE(short,       short);
CMETA_TYPE(int,         int);
CMETA_TYPE(long,        long);
CMETA_TYPE(long long,   longlong);

CMETA_TYPE(unsigned char,        uchar);
CMETA_TYPE(unsigned short,       ushort);
CMETA_TYPE(unsigned int,         uint);
CMETA_TYPE(unsigned long,        ulong);
CMETA_TYPE(unsigned long long,   ulonglong);

CMETA_TYPE(float,       float);
CMETA_TYPE(double,      double);
CMETA_TYPE(long double, longdouble);

typedef void   *cmeta_pointer;

/**
 * All the 27 default types of CMETA library.
 * Use this define to make a full structure
 * of the library (in the CMeta.c file):
 * CMETA_FUNC_READ_GEN(CMETA_ALL_TYPES);
 * CMETA_FUNC_SET_GEN(CMETA_ALL_TYPES);
 * This will generate ALL functions associated with
 * these types to read/write them from CMETA structures.
 */
#define CMETA_ALL_TYPES         \
    char,       pchar,          \
    short,      pshort,         \
    int,        pint,           \
    long,       plong,          \
    longlong,   plonglong,      \
    uchar,      puchar,         \
    ushort,     pushort,        \
    uint,       puint,          \
    ulong,      pulong,         \
    ulonglong,  pulonglong,     \
    float,      pfloat,         \
    double,     pdouble,        \
    longdouble, plongdouble,    \
                pointer

/**
 * Member definition.
 * @name: The name of the member.
 * @type: The type of the member.
 * @size: The size of this type, in bytes.
 * @offset: The offset of the member in data structure, in bytes.
 */
struct  meta_type {
    const char const    *name;
    const char const    *type;
    const unsigned int  size;
    const unsigned int  offset;
};

/**
 * Meta structure definition
 * @name: The name of the structure
 * @memCount: The count of members in the structure
 * @members[]: Each members of the structure
 */
struct meta_struct {
    const unsigned int memCount;
    const struct meta_type const members[];
};

struct linked_meta {
    const struct meta_struct const *meta;
    const struct linked_meta *next;
};

/**
 *  Get meta structure in the given ptr :
 *      - If the given pointer is a pointer on a meta structure, then it isn't changed and the function returns 0
 *      - If it's a pointer on a datastructure, the pointer is set to the contained meta structure and the function returns 1
 *      - If no meta is found, the *ptr is set to NULL and the function returns -1.
 */
int cmeta_get_meta(const struct meta_struct **meta);

/**
 * Debug purpose : Show the meta structure of the given struct pointer.
 * Can be a meta structure pointer, or a data structure pointer built with CMETA_STRUCT_BUILD and initiated with CMETA_INIT
 */
void    cmeta_print_types(const void *ptr);

/**
 * Debug purpose : Show the meta structure of all the registered symbols.
 */
void    cmeta_print_all_symbols();

/**
 * TECHNICAL STUFF BELOW
 */
extern const struct linked_meta *cmeta_metastructures;
extern const char * const cmeta_type_print_associations[][2];

/**
 * Technical FOR_EACH stuff. see below the FOR_EACH macro
 */
#define FOR_EACH_1(what, d, x, ...) what(d, x)
#define FOR_EACH_2(what, d, x, ...) what(d, x) FOR_EACH_1(what, d, __VA_ARGS__)
#define FOR_EACH_3(what, d, x, ...) what(d, x) FOR_EACH_2(what, d, __VA_ARGS__)
#define FOR_EACH_4(what, d, x, ...) what(d, x) FOR_EACH_3(what, d, __VA_ARGS__)
#define FOR_EACH_5(what, d, x, ...) what(d, x) FOR_EACH_4(what, d, __VA_ARGS__)
#define FOR_EACH_6(what, d, x, ...) what(d, x) FOR_EACH_5(what, d, __VA_ARGS__)
#define FOR_EACH_7(what, d, x, ...) what(d, x) FOR_EACH_6(what, d, __VA_ARGS__)
#define FOR_EACH_8(what, d, x, ...) what(d, x) FOR_EACH_7(what, d, __VA_ARGS__)
#define FOR_EACH_9(what, d, x, ...) what(d, x) FOR_EACH_8(what, d, __VA_ARGS__)
#define FOR_EACH_10(what, d, x, ...) what(d, x) FOR_EACH_9(what, d, __VA_ARGS__)
#define FOR_EACH_11(what, d, x, ...) what(d, x) FOR_EACH_10(what, d, __VA_ARGS__)
#define FOR_EACH_12(what, d, x, ...) what(d, x) FOR_EACH_11(what, d, __VA_ARGS__)
#define FOR_EACH_13(what, d, x, ...) what(d, x) FOR_EACH_12(what, d, __VA_ARGS__)
#define FOR_EACH_14(what, d, x, ...) what(d, x) FOR_EACH_13(what, d, __VA_ARGS__)
#define FOR_EACH_15(what, d, x, ...) what(d, x) FOR_EACH_14(what, d, __VA_ARGS__)
#define FOR_EACH_16(what, d, x, ...) what(d, x) FOR_EACH_15(what, d, __VA_ARGS__)
#define FOR_EACH_17(what, d, x, ...) what(d, x) FOR_EACH_16(what, d, __VA_ARGS__)
#define FOR_EACH_18(what, d, x, ...) what(d, x) FOR_EACH_17(what, d, __VA_ARGS__)
#define FOR_EACH_19(what, d, x, ...) what(d, x) FOR_EACH_18(what, d, __VA_ARGS__)
#define FOR_EACH_20(what, d, x, ...) what(d, x) FOR_EACH_19(what, d, __VA_ARGS__)
#define FOR_EACH_21(what, d, x, ...) what(d, x) FOR_EACH_20(what, d, __VA_ARGS__)
#define FOR_EACH_22(what, d, x, ...) what(d, x) FOR_EACH_21(what, d, __VA_ARGS__)
#define FOR_EACH_23(what, d, x, ...) what(d, x) FOR_EACH_22(what, d, __VA_ARGS__)
#define FOR_EACH_24(what, d, x, ...) what(d, x) FOR_EACH_23(what, d, __VA_ARGS__)
#define FOR_EACH_25(what, d, x, ...) what(d, x) FOR_EACH_24(what, d, __VA_ARGS__)
#define FOR_EACH_26(what, d, x, ...) what(d, x) FOR_EACH_25(what, d, __VA_ARGS__)
#define FOR_EACH_27(what, d, x, ...) what(d, x) FOR_EACH_26(what, d, __VA_ARGS__)
#define FOR_EACH_28(what, d, x, ...) what(d, x) FOR_EACH_27(what, d, __VA_ARGS__)
#define FOR_EACH_29(what, d, x, ...) what(d, x) FOR_EACH_28(what, d, __VA_ARGS__)
#define FOR_EACH_30(what, d, x, ...) what(d, x) FOR_EACH_29(what, d, __VA_ARGS__)
#define FOR_EACH_31(what, d, x, ...) what(d, x) FOR_EACH_30(what, d, __VA_ARGS__)
#define FOR_EACH_32(what, d, x, ...) what(d, x) FOR_EACH_31(what, d, __VA_ARGS__)
#define FOR_EACH_(N, what, d, x, ...) CONCATENATE(FOR_EACH_, N)(what, d, x, __VA_ARGS__)

/**
 * Apply a macro to each elements from X to the 32'nd element, called as what(d, curent_element)
 */
#define FOR_EACH(what, d, x, ...) FOR_EACH_(FOR_EACH_NARG(x, __VA_ARGS__), what, d, x, __VA_ARGS__)

/**
 * Count up to 16 varargs parameters.
 */
#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) FOR_EACH_ARG_N(__VA_ARGS__)
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, N, ...) N
#define FOR_EACH_RSEQ_N() 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define PARAMERISE(a, b) a, b
#define DEPLOY(a, x) a x

#define CMETA_TYPE_DEF(type, name)  CMETA(type) name;
#define CMETA_TYPE_DEF_(_, params)  DEPLOY(CMETA_TYPE_DEF, params) //_ == unused

#define CMETA_TYPE_BUILD1(st, type, name) { #name, STRINGIZE(type), sizeof(CMETA(type)), offsetof(st, name) },
#define CMETA_TYPE_BUILD1_(type, params) CMETA_TYPE_BUILD1(type, params)
#define CMETA_TYPE_BUILD1__(type, params) CMETA_TYPE_BUILD1_(type, DEPLOY(PARAMERISE, params))

/*
 * This function is used in place of addSymbol function
 * for idempotence.
 */
void cmeta_do_nothing();

/*
 * Define metadata structure (USE IN .H)
 */
#define CMETA_STRUCT_DEF_(name, ...)	        \
typedef struct {                                \
	t_object	base;							\
    const struct meta_struct *meta;       		\
    FOR_EACH(CMETA_TYPE_DEF_, , __VA_ARGS__  )  \
} name;                                         \
extern const struct meta_struct CMETA(name);    \
extern void    (*cmeta_##name##_addSymbol)();

/**
 * Build metadata global variable structure (USE IN .C)
 */
#define CMETA_STRUCT_BUILD_(name, ...)              \
const struct meta_struct CMETA(name) = {            \
    FOR_EACH_NARG(__VA_ARGS__),                     \
    { FOR_EACH(CMETA_TYPE_BUILD1__, name, __VA_ARGS__) }    \
};                                                  \
static struct linked_meta metalink_##name = {       \
            &CMETA(name), NULL                      \
};                                                  \
static void    cmeta_##name##_addSymbol_do()        \
{                                                   \
    metalink_##name.next = cmeta_metastructures;    \
    cmeta_metastructures = &metalink_##name;        \
    cmeta_##name##_addSymbol = &cmeta_do_nothing;   \
}                                                   \
void (*cmeta_##name##_addSymbol)() = cmeta_##name##_addSymbol_do;

/**
 * Function definition for getting a value based on the member name
 */
#define CMETA_FUNC_READ_DEF(d, T)\
CMETA(T) CMETA_READ(T, const void *ptr, const char *memname, const struct meta_type **metatype) {\
    unsigned int i;\
    const struct meta_struct *meta = (const struct meta_struct *)ptr;\
    if (ptr && memname && cmeta_get_meta(&meta) == 1) {\
        for (i = 0; i < meta->memCount; i++) {\
            if (!strcmp(meta->members[i].name, memname)) {\
                if (!strcmp(meta->members[i].type, #T)) {\
                    if (metatype)\
                        *metatype = &meta->members[i];\
                    return *((CMETA(T) *)(((char *)ptr) + meta->members[i].offset));\
                }\
            }\
        }\
    }\
    if (metatype)\
        *metatype = NULL;\
    return (CMETA(T))0;\
}

#define CMETA_FUNC_READ_ASSOC_DEF(d, T)\
    {#T, &cmeta_read_cmeta_##T},\

/**
 * Function definition for setting a value based on the member name.
 * Return int value such as :
 * 0 - No error, the value is set.
 * 1 - Error, the member is not found
 * 2 - Error, the member don't have the given type
 * -1 - Error, a parameter is incorrect (NULL ptr/memname, or ptr not a cmeta compatible pointer)
 */
#define CMETA_FUNC_SET_DEF(d, T)\
int CMETA_SET(T, const void *ptr, const char *memname, CMETA(T) new_value) {\
    unsigned int i;\
    const struct meta_struct *meta = (const struct meta_struct *)ptr;\
    if (ptr && memname && cmeta_get_meta(&meta) == 1) {\
        for (i = 0; i < meta->memCount; i++) {\
            if (!strcmp(meta->members[i].name, memname)) {\
                if (!strcmp(meta->members[i].type, #T)) {\
                    *((CMETA(T) *)(((char *)ptr) + meta->members[i].offset)) = new_value;\
                    return 0;\
                }\
                return 2;\
            }\
        }\
        return 1;\
    }\
    return -1;\
}

#define CMETA_FUNC_SET_ASSOC_DEF(d, T)\
    {#T, &cmeta_set_cmeta_##T},\

/**
 * Associations between cmeta types and related getter/setter functions
 */
typedef struct {const char *type; const void *func;} cmeta_type_func_associations;
extern const cmeta_type_func_associations cmeta_type_read_associations[];

#define CMETA_FUNC_READ_GEN(...)\
    FOR_EACH(CMETA_FUNC_READ_DEF, unused, __VA_ARGS__)\
    const cmeta_type_func_associations cmeta_type_read_associations[] = {\
        FOR_EACH(CMETA_FUNC_READ_ASSOC_DEF, unused, __VA_ARGS__)\
    };

extern const cmeta_type_func_associations cmeta_type_set_associations[];
#define CMETA_FUNC_SET_GEN(...)\
    FOR_EACH(CMETA_FUNC_SET_DEF, unused, __VA_ARGS__)\
    const cmeta_type_func_associations cmeta_type_set_associations[] = {\
        FOR_EACH(CMETA_FUNC_SET_ASSOC_DEF, unused, __VA_ARGS__)\
    };


#endif /* !_CMETA_H_ */
