#include <stdio.h>
#include "string.h"
#include "splitted.h"

#include "foreach.h"

void		spl_del(t_object *ptr)
{
  t_splitted	*s;

  if (!ptr)
    return ;
  s = (t_splitted *)ptr;
  free(s->ptr);
  delete(s->words);
}

CMETA_STRUCT_BUILD(t_splitted_DEFINITION)
{
  t_splitted	*s;
  char		*chars;
  size_t	i;
  size_t	len;

  if (!args.ptr)
    return (NULL);
  if ((s = newObject(t_splitted, &spl_del)) == NULL ||
      (s->words = new(t_vector)) == NULL)
    return (NULL);
  chars = (args.splitChars ? args.splitChars : " ");
  len = strlen(args.ptr);
  s->ptr = strdup(args.ptr);
  i = 0;
  for (i = 0; i < len; ++i)
    {
      for ( ; i < len && strchr(chars, s->ptr[i]); ++i)
	s->ptr[i] = 0;
      if (s->ptr[i] && i < len)
	  vector_push_back(s->words, s->ptr + i);
      i += strcspn(s->ptr + i, chars) - 1;
    }
  return (s);
}
