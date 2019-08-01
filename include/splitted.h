#ifndef SPLITTED_H_
# define SPLITTED_H_

# include "object.h"
# include "vector.h"

# define t_splitted_DEFINITION	\
	t_splitted,					\
	(pChar, ptr),				\
	(pChar, splitChars),		\
	(t_pvector, words)

CMETA_STRUCT_DEF(t_splitted_DEFINITION);

#endif /* !SPLITTED_H_ */
