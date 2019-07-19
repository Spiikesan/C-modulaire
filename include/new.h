#ifndef NEW_H_
# define NEW_H_

# include <stdlib.h>

/*
 ** Warning inutile, la norme de compilation exige que les champs
 ** non explicitement initialisés soient mis à 0. Norme que GCC respecte.
 */
# pragma GCC diagnostic ignored "-Wmissing-field-initializers"

typedef struct s_object t_object;

typedef void (*func_del)(void *ptr);
typedef void (*func_str)(t_object *o);

# define OBJECT_MAGIC (0xADAF0BECU)

/*
 * Generate default magic for types (incremental)
 * You must not suppose the given value, because it depends on use of this macro.
 */
# define DEFAULT_MAGIC __COUNTER__

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

typedef struct s_object_init {
	size_t obj_size;
	const char *name;
	unsigned int type_magic;
	func_del del;
	func_str str;
} t_object_init;

typedef struct s_magic {
	unsigned int obj;
	unsigned int type;
	//unsigned int instance; //Is it really usefull ?
} t_magic;

struct s_object {
	t_magic magic;
	t_object *next;
	t_object *prev;
	func_del del;
	func_str to_str;
	const char *name;
};

t_object *t_object_new(t_object_init var);
void _delete(t_object *obj);
void _reg_object(t_object *obj);
void _unreg_object(t_object *obj);

# define new(type, ...) (type##_new((type##_init){__VA_ARGS__}))

# define newObject(type, ...) (type *)new(t_object, sizeof(type), #type, MAGIC_##type+1, ##__VA_ARGS__)

# define delete(var) _delete((t_object *)var)

#endif /* !NEW_H_ */
