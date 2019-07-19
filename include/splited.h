#ifndef SPLITED_H_
# define SPLITED_H_

# include "new.h"
# include "vector.h"

# define MAGIC_t_splited DEFAULT_MAGIC

typedef struct	s_splited_init
{
  char		*str;
  char		*splitchars;
}		t_splited_init;

typedef struct	s_splited
{
  t_object	__obj__;
  t_vector	*words;
  char		*ptr;
}		t_splited;

t_splited		*t_splited_new(t_splited_init var);

#endif /* !SPLITED_H_ */
