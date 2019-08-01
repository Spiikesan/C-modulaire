#ifndef PAIR_H_
# define PAIR_H_

# include "object.h"

# define t_pair_DEFINITION	\
	t_pair,					\
	(Pointer, first),		\
	(Pointer, second)

CMETA_STRUCT_DEF(t_pair_DEFINITION);

typedef t_pair *t_ppair;

#endif /* !PAIR_H_ */
