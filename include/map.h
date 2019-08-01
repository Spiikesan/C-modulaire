#ifndef MAP_H_
# define MAP_H_

/*
** Malloc/free, size_t
*/
# include <stdlib.h>

/*
** new/delete
*/
# include "object.h"

/*
** pair
*/
# include "pair.h"

/*
** Define de configuration
*/
# define MAP_MAX_DIFF	(8)

# define MAGIC_t_map DEFAULT_MAGIC

/*
** Defines de retours.
*/
# define MAP_ARGS	(-1)
# define MAP_FUNC	(-2)
# define MAP_NOMORE	(-3)
# define MAP_NOERR	(0)

/*
** Ce n'est pas une fonction car le type n'est pas récupérable autrement.
*/
# define MGET(type, map, key) ((type)(map_get((t_map *)map, key)))

typedef int		(*t_compar_func)(const void *a, const void *b);

typedef t_ppair *t_ppairArray;

# define t_map_DEFINITION		\
	t_map,						\
	(uLong, size),				\
	(t_ppairArray, array),		\
	(t_compar_func, compar),	\
	(Pointer, defaultValue),	\
	(uLong, alloc)

CMETA_STRUCT_DEF(t_map_DEFINITION);

typedef t_map *t_pmap;

size_t	map_size(const t_map *m);
int	map_add(t_map *m, void *key, void *value);
int	map_remove(t_map *m, const void *key);
void	*map_get(const t_map *m, const void *key);

#endif /* !MAP_H_ */
