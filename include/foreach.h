#ifndef FOREACH_H_
# define FOREACH_H_

# include "object.h"

/*
** To correctly works with foreach, the container must be like this :
** # define t_myObject_DEFINITION	\
** 		t_myObject,					\
**   	CONTAINER_ELEMENTS,			\
**   	...
**
**
** Then use the macro like this :
** FOREACH(elem_type, elem_name, container, {
**   DoSomething(elem_name);
**   DoSomethingElse(elem_name);
** })
**
** Curly braces are optional if there is only one statement after it:
** FOREACH(elem_type, elem_name, container, DoSomething(elem_name))
**
** TODO: Function based iterators for the loop and container management. More secure, and less dirty.
** It will permit non-array based iterators (like linked lists or trees)
** -> One to get the first pointer,
** -> One to get the last pointer,
** -> One to get next pointer from current one
** -> Maybe one to get the real value from the iterator ?
*/

typedef Pointer *pPointer;

# define CONTAINER_ELEMENTS \
	(uLong, size),			\
	(pPointer, array)

/*
** Utilities for the FOREACH macro
*/
# define FIRST(t, c) (*(t **)((char *)c + sizeof(t_object) + sizeof(uLong)))
# define LAST(t, c) (FIRST(t, c) + *((uLong *)(((char *)c) + sizeof(t_object))))

# define FE_INIT(t, e, c, id) { t *_cur_##id = FIRST(t, c); for (t e = *_cur_##id
# define FE_COND(t, e, c, id) _cur_##id != LAST(t, c)
# define FE_END(t, e, id) e = *(++_cur_##id))

# define FOREACH_UNIQUE(t, e, c, id) FE_INIT(t, e, c, id); FE_COND(t, e, c, id); FE_END(t, e, id)
# define FOREACH(t, e, c, b) FOREACH_UNIQUE(t, e, c, __COUNTER__) b; }

#endif /* !FOREACH_H_ */
