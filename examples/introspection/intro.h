#ifndef INTRO_H_
# define INTRO_H_

# include "object.h"

/**
 * Not mandatory to name it like this.
 */
# define t_intro_DEFINITION	\
	t_intro,			\
	(Int, anInteger),	\
	(pChar, aString),	\
	(Double, aDouble)

/**
 * Generate the struct.
 */
CMETA_STRUCT_DEF(t_intro_DEFINITION);

#endif /* INTRO_H_ */
