#ifndef CIRCULARBUFF_H_
# define CIRCULARBUFF_H_

/*
** Malloc/free, size_t
*/
# include <stdlib.h>

/*
** new/delete
*/
# include "new.h"

# define MAGIC_t_circularBuff DEFAULT_MAGIC

/*
** Defines de retours.
*/
# define CBF_NOMORE	(NULL)
# define CBF_NOERR	(0)
# define CBF_NOPLACE	(1)

# define CBGET(type, cbf) ((type)(circularBuff_get(cbf)))
# define CBPUT(cbf, elemt) (circularBuff_put(cbf, (void *)elemt))
# define CBSIZE(cbf) (circularBuff_remain(cbf))

/*
** Utilisé pour le new (initialisation).
*/
typedef struct	s_circularBuff_init
{
  int		size;
}		t_circularBuff_init;

typedef struct	s_circularBuff
{
  t_object	__obj__;
  size_t	size;
  void		**array;
  size_t	alloc;
  size_t	remain;
  size_t	read;
  size_t	write;
}		t_circularBuff;

t_circularBuff	*t_circularBuff_new(t_circularBuff_init var);
void		cb_del(void *v);
void		*circularBuff_get(t_circularBuff *v);
int		circularBuff_put(t_circularBuff *v, void *elem);
size_t		circularBuff_remain(t_circularBuff *v);

#endif /* !CIRCULARBUFF_H_ */
