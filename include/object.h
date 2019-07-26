#ifndef OBJECT_H_
# define OBJECT_H_

# include "new.h"
# include "CMeta.h"

/*
** Get the object substruct
*/
# define OBJ(x) ((t_object *)(x))

/*
** Check if given pointer is an object using magic
*/
# define IS_OBJ(x) ((x) && OBJ(x)->magic.obj == OBJECT_MAGIC)

/*
** Get type magic
*/
# define OBJ_MAGIC(x) (OBJ(x)->magic.type)

/*
** Get the name
*/
# define OBJ_NAME(x) (get_object_name(OBJ(x)))

/*
** Compare two objects type
*/
# define OBJ_SAME(x, y) (is_same_objects(OBJ(x), OBJ(y)))

/*
** Get the string representation of the object
*/
# define OBJ_STR(x) (object_to_string(OBJ(x)))

/**
 * To use object-like structs, you must follow these rules : (each word "type" must be replaced by your own)
 *  - The first element of your struct MUST be the "t_object" type
 *  - You have to create a type_init type as a structure for arguments to the type_new function. This structure can be empty.
 *  - You have to create a type_new function that take an unique type_init type argument as parameter
 *  - In your type_new function, you must call newObject(type, del_func, string_func)
 *    - The type parameter is mandatory.
 *    - The del_func is called when the object is destroyed using delete(object).
 *    - The string_func is used to generate a string representation of the object when OBJ_NAME(object) is called.
 *      If it's not given, the name of the type is given.
 *  - You must create a MAGIC_type define with DEFAULT_MAGIC as a value to be sure of uniqueness.
 */

t_object *t_object_new(t_object_init var);

void _delete(t_object *obj);

/*
** Return the object name, or "Null"
*/
const char	*get_object_name(const t_object *o);

/*
** Compare objects name.
** Return -1 if at least one of them is NULL
** Return 1 if they are the same type (with same name)
** Return 0 otherwise
*/
int	is_same_objects(const t_object *a, const t_object *b);

/*
** Get the string representation of the object
*/
const char	*object_to_string(const t_object *o);

#endif /* OBJECT_H_ */
