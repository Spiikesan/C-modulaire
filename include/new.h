#ifndef NEW_H_
# define NEW_H_

# define OBJECT_MAGIC (0xADAF0BECU)

/*
 ** Useless warning.
 */
# pragma GCC diagnostic ignored "-Wmissing-field-initializers"

typedef struct s_object t_object, *t_pobject;

struct meta_struct;

typedef void (*func_del)(t_object *ptr);
typedef const char *(*func_str)(const t_object *o);

/**
 * All is here and not in object.h to avoir circular inclusion
 */
typedef struct s_object_init {
	unsigned int obj_size;
	unsigned int type_magic;
	const struct meta_struct *meta;
	func_del del;
	func_str str;
} t_object_init;

typedef struct s_reference {
	unsigned int magic;
	unsigned int type;
	//unsigned int instance; //Is it really usefull ? can be used as references...
} t_reference;

struct s_object {
	t_reference ref;
	const struct meta_struct *meta;
	t_object *next;
	t_object *prev;
	func_del del;
	func_str to_str;
};

/*
 * Generate default magic for types (incremental)
 * You must not suppose the given value, because it depends on use of this macro.
 */
# define DEFAULT_MAGIC __COUNTER__

# define new(type, ...) (type##_new((type##_init){__VA_ARGS__}))

# define newObject(type, ...) (type *)new(t_object, sizeof(type), DEFAULT_MAGIC+1, &CMETA(type), ##__VA_ARGS__)

# define delete(var) {_delete((t_object *)var); var = NULL;}


#endif /* !NEW_H_ */
