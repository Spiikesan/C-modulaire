#ifndef VECTOR_H_
# define VECTOR_H_

/*
** Malloc/free, size_t
*/
# include <stdlib.h>

/*
** memset
*/
# include <string.h>

/*
** new/delete
*/
# include "object.h"
# include "foreach.h"

/*
** Define de configuration
*/
# define VEC_MAX_DIFF	(8)

# define MAGIC_t_vector DEFAULT_MAGIC

/*
** Defines de retours.
*/
# define VEC_ARGS	(-1)
# define VEC_FUNC	(-2)
# define VEC_NOMORE	(-3)
# define VEC_NOERR	(0)

/*
** Macros d'accession / modification
*/
# define VGET(type, vec, index) (*(type *)(vector_at(vec, index)))
# define VGETP(type, vec, index) ((type)(vector_at(vec, index)))
# define VSET(type, vec, index, elem) (VGET(type, vec, index) = elem)
# define VSETP(vec, index, elem) (vector_set(vec, index, (void *)elem))

# define t_vector_DEFINITION	\
	t_vector,					\
	CONTAINER_ELEMENTS,			\
	(uLong, alloc)

CMETA_STRUCT_DEF(t_vector_DEFINITION);

typedef t_vector *t_pvector;

int		vector_push_back(t_vector *v, void *elem);
int		vector_pop_back(t_vector *v);
int		vector_set(t_vector *v, size_t index, void *elem);

/*
** vector_accessors.c
*/
size_t		vector_size(t_vector *v);
size_t		vector_alloc(t_vector *v);
void		*vector_at(t_vector *v, size_t index);

#endif /* !VECTOR_H_ */
