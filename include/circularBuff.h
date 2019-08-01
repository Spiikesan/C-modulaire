#ifndef CIRCULARBUFF_H_
# define CIRCULARBUFF_H_

/*
** Malloc/free, size_t
*/
# include <stdlib.h>

/*
** new/delete
*/
# include "object.h"
# include "foreach.h"

# define MAGIC_t_circularBuff DEFAULT_MAGIC

/*
** Defines de retours.
*/
# define CBF_NOMORE		(NULL)
# define CBF_NOERR		(0)
# define CBF_NOPLACE	(1)

# define CBGET(type, cbf) ((type)(circularBuff_get(cbf)))
# define CBPUT(cbf, elemt) (circularBuff_put(cbf, (void *)elemt))
# define CBSIZE(cbf) (circularBuff_remain(cbf))

# define t_circularBuff_DEFINITION	\
		t_circularBuff,				\
		CONTAINER_ELEMENTS, 		\
		(uLong, alloc),				\
		(uLong, remain),			\
		(uLong, read),				\
		(uLong, write)

CMETA_STRUCT_DEF(t_circularBuff_DEFINITION);

void	*circularBuff_get(t_circularBuff *v);
int		circularBuff_put(t_circularBuff *v, void *elem);
size_t	circularBuff_remain(t_circularBuff *v);

#endif /* !CIRCULARBUFF_H_ */
