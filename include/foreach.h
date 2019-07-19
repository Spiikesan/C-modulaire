#ifndef FOREACH_H_
# define FOREACH_H_

# include "new.h"

/*
** To correctly works with foreach, the container must be in the form :
** struct s_<container>
** {
**   t_object	__obj__;
**   size_t	nElemsInArray;
**   void	**arrayOfElements;
**   ...
** };
**
** Then use the macro like this :
** FOREACH(elem_type, elem_name, container)
** {
**   DoSomething(elem_name);
** }
**
** Curly braces are optional if there is only one line after it, like a classic for loop
*/

/*
** Utilities for the FOREACH macro
*/
# define FIRST(t, c) (*(t **)((void *)c + sizeof(t_object) + sizeof(size_t)))
# define LAST(t, c) (FIRST(t, c) + *((size_t *)(((void *)c) + sizeof(t_object))))

# define FE_INIT(t, e, c, id) { t *_cur_##id = FIRST(t, c); for (t e = *_cur_##id
# define FE_COND(t, e, c, id) _cur_##id != LAST(t, c)
# define FE_END(t, e, id) e = *(++_cur_##id))

# define FOREACH_UNIQUE(t, e, c, id) FE_INIT(t, e, c, id); FE_COND(t, e, c, id); FE_END(t, e, id)
# define FOREACH(t, e, c, b) FOREACH_UNIQUE(t, e, c, __COUNTER__) b }

#endif /* !FOREACH_H_ */
