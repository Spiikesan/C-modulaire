#include <stdio.h>
#include "string.h"
#include "splited.h"

#include "foreach.h"

void		spl_del(void *ptr)
{
  t_splited	*s;

  if (!ptr)
    return ;
  s = ptr;
  free(s->ptr);
  delete(s->words);
}

t_splited	*t_splited_new(t_splited_init var)
{
  t_splited	*s;
  char		*chars;
  size_t	i;
  size_t	len;

  if (!var.str)
    return (NULL);
  if ((s = newObject(t_splited, &spl_del)) == NULL ||
      (s->words = new(t_vector)) == NULL)
    return (NULL);
  chars = (var.splitchars ? var.splitchars : " ");
  len = strlen(var.str);
  s->ptr = strdup(var.str);
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
